/*
This source file is part of Solipsis
    (Solipsis is an opensource decentralized Metaverse platform)
For the latest info, see http://www.solipsis.org/

Copyright (C) 2006-2008 ANR-RIAM (IRISA, Archivideo, Artefacto, Rennes 2 University, Orange Labs)
Author JAN Gregory

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __PhysXHelpers_h__
#define __PhysXHelpers_h__

#include "Ogre.h"

#include "NxPhysics.h"
#include "NxStream.h"

class UserStream : public NxStream
	{
	public:
								UserStream(const char* filename, bool load);
	virtual						~UserStream();

	virtual		NxU8			readByte()								const;
	virtual		NxU16			readWord()								const;
	virtual		NxU32			readDword()								const;
	virtual		float			readFloat()								const;
	virtual		double			readDouble()							const;
	virtual		void			readBuffer(void* buffer, NxU32 size)	const;

	virtual		NxStream&		storeByte(NxU8 b);
	virtual		NxStream&		storeWord(NxU16 w);
	virtual		NxStream&		storeDword(NxU32 d);
	virtual		NxStream&		storeFloat(NxReal f);
	virtual		NxStream&		storeDouble(NxF64 f);
	virtual		NxStream&		storeBuffer(const void* buffer, NxU32 size);

				FILE*			fp;
	};

class MemoryWriteBuffer : public NxStream
	{
	public:
								MemoryWriteBuffer();
	virtual						~MemoryWriteBuffer();
				void			clear();

	virtual		NxU8			readByte()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		NxU16			readWord()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		NxU32			readDword()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		float			readFloat()								const	{ NX_ASSERT(0);	return 0.0f;}
	virtual		double			readDouble()							const	{ NX_ASSERT(0);	return 0.0;	}
	virtual		void			readBuffer(void* buffer, NxU32 size)	const	{ NX_ASSERT(0);				}

	virtual		NxStream&		storeByte(NxU8 b);
	virtual		NxStream&		storeWord(NxU16 w);
	virtual		NxStream&		storeDword(NxU32 d);
	virtual		NxStream&		storeFloat(NxReal f);
	virtual		NxStream&		storeDouble(NxF64 f);
	virtual		NxStream&		storeBuffer(const void* buffer, NxU32 size);

				NxU32			currentSize;
				NxU32			maxSize;
				NxU8*			data;
	};

class MemoryReadBuffer : public NxStream
	{
	public:
								MemoryReadBuffer(const NxU8* data);
	virtual						~MemoryReadBuffer();

	virtual		NxU8			readByte()								const;
	virtual		NxU16			readWord()								const;
	virtual		NxU32			readDword()								const;
	virtual		float			readFloat()								const;
	virtual		double			readDouble()							const;
	virtual		void			readBuffer(void* buffer, NxU32 size)	const;

	virtual		NxStream&		storeByte(NxU8 b)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeWord(NxU16 w)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeDword(NxU32 d)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeFloat(NxReal f)						{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeDouble(NxF64 f)						{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeBuffer(const void* buffer, NxU32 size)	{ NX_ASSERT(0);	return *this;	}

	mutable		const NxU8*		buffer;
	};

using namespace Ogre;

namespace Solipsis {

/** This static class contains several helper methods above Ageia PhysX physics engine.
 */
class PhysXHelpers
{
protected:
    static NxPhysicsSDK* mNxPhysicsSDK;

private:
    /// No instanciation constructor
    PhysXHelpers() {}

public:
    /// Init
    static bool init();
    /// Shutdown
    static bool shutdown();

    /// Get/Set
    static NxPhysicsSDK* getNxPhysicsSDK() { return mNxPhysicsSDK; }

    /// Conversions
    static inline Vector3 NxVec32Vector3(NxVec3 v) { return Vector3(v.x, v.y, v.z); }
    static inline NxVec3 Vector32NxVec3(Vector3 v) { return NxVec3(v.x, v.y, v.z); }
    static inline Quaternion NxQuat2Quaternion(NxQuat q) { return Quaternion(q.w, q.x, q.y, q.z); }
    static inline NxQuat Quaternion2NxQuat(Quaternion q) { return NxQuat(NxVec3(q.x, q.y, q.z), q.w); }

    /// Cook 1 mesh into 1 NxTriangleMesh
    static NxTriangleMesh* cookMesh(const MeshPtr mesh,
        const Vector3& position,
        const Quaternion& orient,
        const Vector3& scale);
};

} // namespace Solipsis

#endif // #ifndef __PhysXHelpers_h__