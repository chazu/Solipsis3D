/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2002
 *     Guido Tack, 2004
 *
 *  Last modified:
 *     $Date: 2008-07-11 09:10:11 +0100 (Fri, 11 Jul 2008) $ by $Author: tack $
 *     $Revision: 7310 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __GECODE_SEARCH_HH__
#define __GECODE_SEARCH_HH__

#include <ctime>

#include "gecode/kernel.hh"

/*
 * Configure linking
 *
 */
#if !defined(GECODE_STATIC_LIBS) && \
    (defined(__CYGWIN__) || defined(__MINGW32__) || defined(_MSC_VER))

#ifdef GECODE_BUILD_SEARCH
#define GECODE_SEARCH_EXPORT __declspec( dllexport )
#else
#define GECODE_SEARCH_EXPORT __declspec( dllimport )
#endif

#else

#ifdef GECODE_GCC_HAS_CLASS_VISIBILITY
#define GECODE_SEARCH_EXPORT __attribute__ ((visibility("default")))
#else
#define GECODE_SEARCH_EXPORT
#endif

#endif

namespace Gecode {

  /// %Search engines
  namespace Search {

    /**
     * \brief %Search configuration
     *
     * \ingroup TaskModelSearch
     */
    namespace Config {
      /// Create a clone after every \a c_d commits
      const unsigned int c_d = 8;
      /// Create a clone during recomputation if distance is greater than \a a_d
      const unsigned int a_d = 2;
    }

    /**
     * \brief %Search engine statistics
     * \ingroup TaskModelSearch
     */
    class Statistics {
    public:
      /// Number of propagation steps
      unsigned long int propagate;
      /// Number of failed nodes in search tree
      unsigned long int fail;
      /// Number of clones created
      unsigned long int clone;
      /// Number of commit operations performed
      unsigned long int commit;
      /// Peak memory allocated
      size_t memory;
      /// Initialize with all numbers zero
      Statistics(void);
    };


    /**
     * \defgroup TaskModelSearchStop Stop-objects for stopping search
     * \ingroup TaskModelSearch
     *
     * Allows to specify various criteria when a search engine should
     * stop exploration. Only exploration but neither recomputation
     * nor propagation will be interrupted.
     *
     */

    /**
     * \brief Base-class for %Stop-object
     * \ingroup TaskModelSearchStop
     */
    class GECODE_SEARCH_EXPORT Stop {
    public:
      /// Default constructor
      Stop(void);
      /// Stop search, if returns true (can be based on statistics \a s)
      virtual bool stop(const Statistics& s) = 0;
      /// Destructor
      virtual ~Stop(void);
    };

    /**
     * \brief %Stop-object based on memory consumption
     *
     * \ingroup TaskModelSearchStop
     */
    class GECODE_SEARCH_EXPORT MemoryStop : public Stop {
    protected:
      /// Size limit
      size_t l;
    public:
      /// Stop if memory limit \a l (in bytes) is exceeded
      MemoryStop(size_t l);
      /// Return current limit
      size_t limit(void) const;
      /// Set current limit to \a l (in bytes)
      void limit(size_t l);
      /// Return true if memory limit is exceeded
      virtual bool stop(const Statistics& s);
    };

    /**
     * \brief %Stop-object based on number of failures
     *
     * The number of failures reported (by the statistics) is the
     * number since the engine started exploration. It is not the
     * number since the last stop!
     * \ingroup TaskModelSearchStop
     */
    class GECODE_SEARCH_EXPORT FailStop : public Stop {
    protected:
      /// Failure limit
      unsigned long int l;
    public:
      /// Stop if failure limit \a l is exceeded
      FailStop(unsigned long int l);
      /// Return current limit
      unsigned long int limit(void) const;
      /// Set current limit to \a l failures
      void limit(unsigned long int l);
      /// Return true if failure limit is exceeded
      virtual bool stop(const Statistics& s);
    };

    /**
     * \brief %Stop-object based on time
     * \ingroup TaskModelSearchStop
     */
    class GECODE_SEARCH_EXPORT TimeStop : public Stop {
    protected:
      /// Clock when execution should stop
      clock_t s;
      /// Current limit in milliseconds
      unsigned long int l;
    public:
      /// Stop if search exceeds \a l milliseconds (from creation of this object)
      TimeStop(unsigned long int l);
      /// Return current limit in milliseconds
      unsigned long int limit(void) const;
      /// Set current limit to \a l milliseconds
      void limit(unsigned long int l);
      /// Reset time to zero
      void reset(void);
      /// Return true if time limit is exceeded
      virtual bool stop(const Statistics& s);
    };

    /**
     * \brief %Search engine options
     *
     * Defines options for search engines. Not all search engines might
     * honor all option values.
     *
     *  - \a c_d as minimal recomputation distance: this guarantees that
     *    a path between two nodes in the search tree for which copies are
     *    stored has at least length \a c_d. That is, in order to recompute
     *    a node in the search tree, \a c_d recomputation steps are needed.
     *    The minimal recomputation distance yields a guarantee on saving
     *    memory compared to full copying: it stores \a c_d times less nodes
     *    than full copying.
     *  - \a a_d as adaptive recomputation distance: when a node needs to be
     *    recomputed and the path is longer than \a a_d, an intermediate copy
     *    is created (approximately in the middle of the path) to speed up
     *    future recomputation. Note that small values of \a a_d can increase
     *    the memory consumption considerably.
     *
     * Full copying corresponds to a maximal recomputation distance 
     * \a c_d of 1.
     *
     * All recomputation performed is based on batch recomputation: batch
     * recomputation performs propagation only once for an entire path
     * used in recomputation.
     */
    class Options {
    public:
      /// Create a clone after every \a c_d commits
      unsigned int c_d;
      /// Create a clone during recomputation if distance is greater than \a a_d
      unsigned int a_d;
      /// Stop object for stopping search
      Stop* stop;
      /// Default options
      GECODE_SEARCH_EXPORT static const Options def;
      /// Initialize with default values
      Options(void);
    };

    /**
     * \brief %Search engine control including memory information
     */
    class EngineCtrl : public Statistics {
    protected:
      /// %Stop-object to be used
      Stop* st;
      /// Whether engine has been stopped
      bool _stopped;
      /// Memory required for a single space
      size_t mem_space;
      /// Memory for the current space (including memory for caching)
      size_t mem_cur;
      /// Current total memory
      size_t mem_total;
    public:
      /// Initialize with stop-object \a st and space size \a sz
      EngineCtrl(Stop* st, size_t sz);
      /// Reset stop information
      void start(void);
      /// Check whether engine must be stopped (with additional stackspace \a sz)
      bool stop(size_t sz);
      /// Check whether engine has been stopped
      bool stopped(void) const;
      /// New space \a s and branching description \a d get pushed on stack
      void push(const Space* s, const BranchingDesc* d);
      /// Space \a s1 is replaced by space \a s2 due to constraining
      void constrained(const Space* s1, const Space* s2);
      /// New space \a s is added for adaptive recomputation
      void adapt(const Space* s);
      /// Space \a s and branching description \a d get popped from stack
      void pop(const Space* s, const BranchingDesc* d);
      /// Space \a s gets used for LAO (removed from stack)
      void lao(const Space* s);
      /// Space \a s becomes current space (\a s = NULL: current space deleted)
      void current(const Space* s);
      /// Reset statistics for space \a s
      void reset(const Space* s);
      /// Reset statistics for failed space
      void reset(void);
    };

    /**
     * \brief %Search tree node for recomputation
     *
     */
    class ReCoNode {
    protected:
      /// Space corresponding to this node (might be NULL)
      Space*               _space;
      /// Current alternative
      unsigned int         _alt;
      /// Braching description
      const BranchingDesc* _desc;
    public:
      /// Node for space \a s with clone \a c (possibly NULL)
      ReCoNode(Space* s, Space* c);

      /// Return space for node
      Space* space(void) const;
      /// Set space to \a s
      void space(Space* s);

      /// Return branching description
      const BranchingDesc* desc(void) const;

      /// Return number for alternatives
      unsigned int alt(void) const;
      /// Test whether current alternative is rightmost
      bool rightmost(void) const;
      /// Move to next alternative
      void next(void);

      /// Free memory for node
      void dispose(void);
    };


    /**
     * \brief Stack of nodes supporting recomputation
     *
     * Maintains the invariant that it contains
     * the path of the node being currently explored. This
     * is required to support recomputation, of course.
     *
     * The stack supports adaptive recomputation controlled
     * by the value of a_d: only if the recomputation
     * distance is at least this large, an additional
     * clone is created.
     *
     */
    class ReCoStack {
    private:
      /// Stack to store node information
      Support::DynamicStack<ReCoNode> ds;
      /// Adaptive recomputation distance
      const unsigned int a_d;
    public:
      /// Initialize with adaptive recomputation distance \a a_d
      ReCoStack(unsigned int a_d);
      /// Push space \a c (a clone of \a s or NULL)
      const BranchingDesc* push(Space* s, Space* c);
      /// Generate path for next node and return BranchingDesc for next node if its type is \a DescType, or NULL otherwise
      template <class DescType>
      const BranchingDesc* nextDesc(EngineCtrl& s, int& alt,
                                    int& closedDescs);
      /// Generate path for next node with BranchingDesc type DescType
      template <class DescType, bool inclusive>
      void closeBranch(EngineCtrl& s);
      /// Generate path for next node and return whether a next node exists
      bool next(EngineCtrl& s);
      /// Return position on stack of last copy
      int lc(Space*& s) const;
      /// Unwind the stack up to position \a l (after failure)
      void unwind(int l);
      /// Commit space \a s as described by stack entry at position \a i
      void commit(Space* s, int i) const;
      /**
       * \brief Recompute space according to path with copying distance \a d
       *
       * The template parameter \a constrained describes whether the stack
       * might contain spaces not propagated (from constraining during
       * branch-and-bound).
       */
      template <bool constrained>
      Space* recompute(unsigned int& d, EngineCtrl& s);
      /// Return number of entries on stack
      int entries(void) const;
      /// Return stack size used
      size_t stacksize(void) const;
      /// Reset stack
      void reset(void);
    };

    /**
     * \brief Depth-first search engine implementation
     *
     */
    class DfsEngine : public EngineCtrl {
    private:
      /// Recomputation stack of nodes
      ReCoStack          rcs;
      /// Current space being explored
      Space*             cur;
      /// Copying recomputation distance
      const unsigned int c_d;
      /// Distance until next clone
      unsigned int       d;
    public:
      /**
       * \brief Initialize engine
       * \param c_d minimal recomputation distance
       * \param a_d adaptive recomputation distance
       * \param st %Stop-object
       * \param sz size of one space
       */
      DfsEngine(unsigned int c_d, unsigned int a_d, Stop* st, size_t sz);
      /// Initialize engine to start at space \a s
      void init(Space* s);
      /// Reset engine to restart at space \a s
      void reset(Space* s);
      /// Reset engine to restart at failed space
      void reset(void);
      /// %Search for next solution
      Space* explore(void);
      /// Return stack size used by engine
      size_t stacksize(void) const;
      /// Destructor
      ~DfsEngine(void);
    };

    /**
     * \brief Depth-first search engine
     *
     * This class implements depth-first exploration for spaces. In order to
     * use depth-first search on subclasses of Space, additional
     * functionality providing the necessary typecasts is available
     * in Gecode::DFS.
     */
    class GECODE_SEARCH_EXPORT DFS {
    protected:
      /// Engine used for exploration
      DfsEngine e;
    public:
      /**
       * \brief Initialize search engine
       * \param s root node (subclass of Space)
       * \param c_d minimal recomputation distance
       * \param a_d adaptive recomputation distance
       * \param st %Stop-object
       * \param sz size of one space
       */
      DFS(Space* s, unsigned int c_d, unsigned int a_d, Stop* st, size_t sz);
      /// Return next solution (NULL, if none exists or search has been stopped)
      Space* next(void);
      /// Return statistics
      Statistics statistics(void) const;
      /// Check whether engine has been stopped
      bool stopped(void) const;
    };

  }

  /**
   * \brief Depth-first search engine
   *
   * This class supports depth-first search for subclasses \a T of
   * Space.
   * \ingroup TaskModelSearch
   */
  template <class T>
  class DFS : public Search::DFS {
  public:
    /// Initialize search engine for space \a s with options \a o
    DFS(T* s, const Search::Options& o=Search::Options::def);
    /// Return next solution (NULL, if none exists or search has been stopped)
    T* next(void);
  };

  /// Invoke depth-first search engine for subclass \a T of space \a s with options \a o
  template <class T>
  T* dfs(T* s, const Search::Options& o=Search::Options::def);


  namespace Search {

    /**
     * \brief Probing engine for %LDS
     *
     */
    class ProbeEngine : public EngineCtrl {
    protected:
      /// %Node in the search tree for %LDS
      class ProbeNode {
      private:
        /// %Space of current node
        Space*               _space;
        /// Branching description
        const BranchingDesc* _desc;
        /// Next alternative to try
        unsigned int         _alt;
      public:
        /// Initialize with node \a s, description \a d, and alternative \a a
        ProbeNode(Space* s, const BranchingDesc* d, unsigned int a);
        /// Return space
        Space* space(void) const;
        /// Return branching description
        const BranchingDesc* desc(void) const;
        /// Return next alternative
        unsigned int alt(void) const;
        /// %Set next alternative
        void next(void);
      };
      /// %Stack storing current path in search tree
      Support::DynamicStack<ProbeNode> ds;
      /// Current space
      Space* cur;
      /// Current discrepancy
      unsigned int d;
      /// Whether entire search space has been exhausted
      bool exhausted;
    public:
      /// Initialize for spaces of size \a s
      ProbeEngine(Stop* st, size_t s);
      /// Initialize with space \a s and discrepancy \a d
      void init(Space* s, unsigned int d);
      /// Reset with space \a s and discrepancy \a d
      void reset(Space* s, unsigned int d);
      /// Return stack size used by engine
      size_t stacksize(void) const;
      /// Destructor
      ~ProbeEngine(void);
      /// %Search for next solution
      Space* explore(void);
      /// Test whether probing is done
      bool done(void) const;
    };

    /**
     * \brief Limited discrepancy search engine
     */
    class GECODE_SEARCH_EXPORT LDS {
    protected:
      Space*       root;        ///< Root node for problem
      unsigned int d_cur;       ///< Current discrepancy
      unsigned int d_max;       ///< Maximal discrepancy
      bool         no_solution; ///< Solution found for current discrepancy
      ProbeEngine  e;           ///< The probe engine
    public:
      /** Initialize engine
       * \param s root node
       * \param d maximal discrepancy
       * \param st %Stop-object
       * \param sz size of space
       */
      LDS(Space* s, unsigned int d, Stop* st, size_t sz);
      /// Return next solution (NULL, if none exists or search has been stopped)
      Space* next(void);
      /// Return statistics
      Statistics statistics(void) const;
      /// Check whether engine has been stopped
      bool stopped(void) const;
      /// Destructor
      ~LDS(void);
    };

  }

  /**
   * \brief Limited discrepancy search engine
   * \ingroup TaskModelSearch
   */
  template <class T>
  class LDS : public Search::LDS {
  public:
    /// Initialize engine with \a s as root node and maximal discrepancy \a d
    LDS(T* s, unsigned int d,
        const Search::Options& o=Search::Options::def);
    /// Return next solution (NULL, if none exists or search has been stopped)
    T* next(void);
  };

  /**
   * \brief Invoke limited-discrepancy search for \a s as root node and maximal discrepancy \a d
   * \ingroup TaskModelSearch
   */
  template <class T>
  T* lds(T* s, unsigned int d,
         const Search::Options& o=Search::Options::def);





  /*
   * Best solution search engines
   *
   */

  namespace Search {

    /**
     * \brief Implementation of depth-first branch-and-bound search engines
     */
    class BabEngine : public EngineCtrl {
    public:
      /// Status of the explore function
      enum ExploreStatus {
        ES_SOLUTION,
        ES_CONSTRAIN
      };
    private:
      /// Recomputation stack of nodes
      ReCoStack          rcs;
      /// Current space being explored
      Space*             cur;
      /// Number of entries not yet constrained to be better
      int                mark;
      /// Record which current operation is in progress
      ExploreStatus      es;
      /// Best solution found so far
      Space*             best;
      /// Copying recomputation distance
      const unsigned int c_d;
      /// Distance until next clone
      unsigned int       d;
    public:
      /**
       * \brief Initialize engine
       * \param c_d minimal recomputation distance
       * \param a_d adaptive recomputation distance
       * \param st %Stop-object
       * \param sz size of one space
       */
      BabEngine(unsigned int c_d, unsigned int a_d, Stop* st, size_t sz);
      /// Initialize engine to start at space \a s
      void init(Space* s);
      /**
       * \brief %Search for next better solution
       *
       * If \c ES_SOLUTION is returned, a next better solution has been found.
       * This solution is available from \a s1.
       *
       * If \c ES_CONSTRAIN is returned, the engine requires that the
       * space \a s1 is constrained to be better by the so-far best
       * solution \a s2.
       *
       */
      GECODE_SEARCH_EXPORT
      ExploreStatus explore(Space*& s1, Space*& s2);
      /// Return stack size used by engine
      size_t stacksize(void) const;
      /// Destructor
      ~BabEngine(void);
    };

    /**
     * \brief Depth-first branch-and-bound search engine
     *
     * This class implements depth-first branch-and-bound exploration
     * for spaces. In order to use it on subclasses of Space, additional
     * functionality providing the necessary typecasts is available
     * in Gecode::BAB:
     *
     */
    class GECODE_SEARCH_EXPORT BAB {
    protected:
      /// Engine used for exploration
      BabEngine e;
    public:
      /**
       * \brief Initialize engine
       * \param s root node
       * \param c_d minimal recomputation distance
       * \param a_d adaptive recomputation distance
       * \param st %Stop-object
       * \param sz size of one space
       */
      BAB(Space* s, unsigned int c_d, unsigned int a_d, Stop* st, size_t sz);
      /// Check whether engine has been stopped
      bool stopped(void) const;
      /// Return statistics
      Statistics statistics(void) const;
    };

  }

  /**
   * \brief Depth-first branch-and-bound search engine
   *
   * Additionally, \a s must implement a member function 
   * \code void constrain(T* t) \endcode
   * Whenever exploration requires to add a constraint
   * to the space \a c currently being explored, the engine
   * executes \c c->constrain(t) where \a t is the so-far
   * best solution.
   * \ingroup TaskModelSearch
   */
  template <class T>
  class BAB : public Search::BAB {
  public:
    /// Initialize engine for space \a s and options \a o
    BAB(T* s, const Search::Options& o=Search::Options::def);
    /// Return next better solution (NULL, if none exists or search has been stopped)
    T* next(void);
  };

  /**
   * \brief Perform depth-first branch-and-bound search for subclass \a T of space \a s and options \a o
   *
   * Additionally, \a s must implement a member function 
   * \code void constrain(T* t) \endcode
   * Whenever exploration requires to add a constraint
   * to the space \a c currently being explored, the engine
   * executes \c c->constrain(t) where \a t is the so-far
   * best solution.
   *
   * \ingroup TaskModelSearch
   */
  template <class T>
  T* bab(T* s, const Search::Options& o=Search::Options::def);



  /**
   * \brief Depth-first restart best solution search engine
   *
   * Additionally, \a s must implement a member function 
   * \code void constrain(T* t) \endcode
   * Whenever exploration requires to add a constraint
   * to the space \a c currently being explored, the engine
   * executes \c c->constrain(t) where \a t is the so-far
   * best solution.
   * \ingroup TaskModelSearch
   */
  template <class T>
  class Restart : public DFS<T> {
  protected:
    /// Root node
    Space* root;
    /// So-far best solution
    Space* best;
  public:
    /// Initialize engine for space \a s and options \a o
    Restart(T* s, const Search::Options& o=Search::Options::def);
    /// Destructor
    ~Restart(void);
    /// Return next better solution (NULL, if none exists or search has been stopped)
    T* next(void);
  };

  /**
   * \brief Perform depth-first restart best solution search for subclass \a T of space \a s and options \a o
   * 
   * Additionally, \a s must implement a member function 
   * \code void constrain(T* t) \endcode
   * Whenever exploration requires to add a constraint
   * to the space \a c currently being explored, the engine
   * executes \c c->constrain(t) where \a t is the so-far
   * best solution.
   * \ingroup TaskModelSearch
   */
  template <class T>
  T* restart(T* s, const Search::Options& o=Search::Options::def);

}

#include "gecode/search/statistics.icc"
#include "gecode/search/stop.icc"
#include "gecode/search/options.icc"
#include "gecode/search/engine-ctrl.icc"

#include "gecode/search/reco-stack.icc"

#include "gecode/search/dfs.icc"
#include "gecode/search/lds.icc"
#include "gecode/search/bab.icc"
#include "gecode/search/restart.icc"

#endif

// STATISTICS: search-any
