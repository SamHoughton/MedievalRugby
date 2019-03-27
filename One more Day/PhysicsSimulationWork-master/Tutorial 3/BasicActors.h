#pragma once

#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	///Plane class
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal=PxVec3(0.f, 1.f, 0.f), PxReal distance=0.f) 
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	///Sphere class
	class Sphere : public DynamicActor
	{
	public:
		//a sphere with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m
		// - denisty: 1kg/m^3
		Sphere(const PxTransform& pose=PxTransform(PxIdentity), PxReal radius=.2f, PxReal density=.2f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxSphereGeometry(radius), density);
		}
	};

	///Box class
	class Bottom : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Bottom(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(30.f,.5f,.5f), PxReal density=500.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};	
	
	class Wall : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Wall(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(30.f,5.5f,1.5f), PxReal density=500.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.5f), density);

			GetShape(1)->setLocalPose(PxTransform(PxVec3(20.f, 6.f,0.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-10.f, 6.f, 0.f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-4.f, 6.f, 0.f)));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(14.f, 6.f, 0.f)));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(8.f, 6.f, 0.f)));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(2.f, 6.f, 0.f)));
		}
	};

	class backWall : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		backWall(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.5f, 5.5f, 29.5f), PxReal density = 500.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(2.f, 1.5f, 1.f), density);

			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, 24.f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, -24.f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, 18.f)));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, -18.f)));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, -12.f)));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(0.f, 6.f, 12.f)));
		}
	};


	class HiddenBox : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		HiddenBox(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(7.5f, 9.5f, 1.5f), PxReal density = 500.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class Top : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Top(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, 30.5f), PxReal density = 500.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};	
	
	class Horse : public DynamicActor
	{
	public:
		Horse(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.f, .5f, 1.5f), PxReal density = 2.f)
			: DynamicActor(pose)
		{
			// Main base of horse
			CreateShape(PxBoxGeometry(dimensions), density);
			// Legs of horse
			CreateShape(PxBoxGeometry(.2f, 0.9f, .2f), 50.f);
			CreateShape(PxBoxGeometry(.2f, 0.9f, .2f), 50.f);
			CreateShape(PxBoxGeometry(.2f, 0.9f, .2f), 50.f);
			CreateShape(PxBoxGeometry(.2f, 0.9f, .2f), 50.f);
			// Tail of horse
			CreateShape(PxBoxGeometry(.1f, 0.2f, .8f), density);
			// Head of the horse
			CreateShape(PxBoxGeometry(0.5f, 0.4f, 0.9f), density);



			// Positioning of objects
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 1.2f, 0.f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-.8f, 0.1f, -1.2f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-.8f, 0.1f, 1.2f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(.8f, 0.1f, 1.2f)));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(.8f, 0.1f, -1.2f)));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(.0f, 1.2f, 1.5f)));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(.0f, 1.8f, -1.8f)));
		}
	};

	class catapult : public DynamicActor
	{
	public:
		//a catapult base
		catapult(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(2.f, 0.3f, 1.f), PxReal density = 10.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			// The right pole of the cactapult
			CreateShape(PxBoxGeometry(0.2f, 2.f, 0.2f), density);
			// The left pole of the cactapult
			CreateShape(PxBoxGeometry(0.2f, 2.f, 0.2f), density);
			// 'wheels' on the back left
			CreateShape(PxCapsuleGeometry(0.3f, 0.01f), density);
			// 'wheels' on the back right
			CreateShape(PxCapsuleGeometry(0.3f, 0.01f), density);
			// The Center beam of the cactapult
			CreateShape(PxBoxGeometry(.2f, 0.1f, 0.9f), density);

			// Right Pole
			GetShape(1)->setLocalPose(PxTransform(PxVec3(2.f, 1.f, 0.9f)));
			// left Pole
			GetShape(2)->setLocalPose(PxTransform(PxVec3(2.f, 1.f, -0.9f)));
			// Back left wheel
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-1.8f, -0.1f, -1.2f)));
			// Back light wheel
			GetShape(4)->setLocalPose(PxTransform(PxVec3(-1.8f, -0.1f, 1.2f)));
			// Centre beam wheel
			GetShape(5)->setLocalPose(PxTransform(PxVec3(2.f, 2.1f, 0.2f)));


		}
	};

	class catapultarm : public DynamicActor
	{
	public:
		//a catapult base
		catapultarm(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.2f, 2.f, .2f), PxReal density  = 0.1f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			// The right pole of the cactapult

		}
	};	
	
	class halfwayLine : public DynamicActor
	{
	public:
		//a catapult base
		halfwayLine(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(20.f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			// The right pole of the cactapult

		}
	};	
	
	class castle : public DynamicActor
	{
	public:
		//a castle base
		castle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(5.2f, 7.f, 5.2f), PxReal density  = 10.1f)
			: DynamicActor(pose)
		{
			// Everything for the castle
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			CreateShape(PxBoxGeometry(1.f, 1.5f, 1.f), density);
			
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-5.2f, 7.2f, .0f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-5.2f, 7.2f, 4.5f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-5.2f, 7.2f, -4.5f)));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(-0.2f, 7.2f, -4.5f)));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(-0.2f, 7.2f, 4.5f)));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(3.2f, 7.2f, 4.5f)));
			GetShape(7)->setLocalPose(PxTransform(PxVec3(3.2f, 7.2f, -4.5f)));
		}
	};

	class Goal : public DynamicActor
	{
	public:
		Goal(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, 3.f, .5f), PxReal density = 100.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), 10.1f);
			CreateShape(PxBoxGeometry(5.f, 0.5f, 0.5f), 10.1f);
			CreateShape(PxBoxGeometry(.5f, 9.f, 0.5f), 10.1f);
			CreateShape(PxBoxGeometry(.5f, 9.f, 0.5f), 10.1f);

			GetShape(1)->setLocalPose(PxTransform(PxVec3(.2f, 3.5f, .0f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(5.f, 9.f, .0f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-5.f, 9.f, .0f)));
		}
	};

	class Capsule : public DynamicActor
	{
	public:
		Capsule(const PxTransform& pose=PxTransform(PxIdentity), PxVec2 dimensions=PxVec2(0.2f,0.2f), PxReal density=1.f) 
			: DynamicActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
		}
	};
	//Distance joint with the springs switched on
	class DistanceJoint : public Joint
	{
	public:
		DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			Damping(1.f);
			Stiffness(1.f);
		}

		void Stiffness(PxReal value)
		{
			((PxDistanceJoint*)joint)->setStiffness(value);
		}

		PxReal Stiffness()
		{
			return ((PxDistanceJoint*)joint)->getStiffness();		
		}

		void Damping(PxReal value)
		{
			((PxDistanceJoint*)joint)->setDamping(value);
		}

		PxReal Damping()
		{
			return ((PxDistanceJoint*)joint)->getDamping();
		}
	};



	//Revolute Joint
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
		}

		void DriveVelocity(PxReal value)
		{
			//wake up the attached actors
			PxRigidDynamic *actor_0, *actor_1;
			((PxRevoluteJoint*)joint)->getActors((PxRigidActor*&)actor_0, (PxRigidActor*&)actor_1);
			if (actor_0)
			{
				if (actor_0->isSleeping())
					actor_0->wakeUp();
			}
			if (actor_1)
			{
				if (actor_1->isSleeping())
					actor_1->wakeUp();
			}
			((PxRevoluteJoint*)joint)->setDriveVelocity(value);
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		PxReal DriveVelocity()
		{
			return ((PxRevoluteJoint*)joint)->getDriveVelocity();
		}

		void SetLimits(PxReal lower, PxReal upper)
		{
			((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
	};

	class Cloth : public Actor
	{
		PxClothMeshDesc mesh_desc;

	public:
		//constructor
		Cloth(PxTransform pose = PxTransform(PxIdentity), const PxVec2& size = PxVec2(1.f, 1.f), PxU32 width = 1, PxU32 height = 1, bool fix_top = true)
		{
			//prepare vertices
			PxReal w_step = size.x / width;
			PxReal h_step = size.y / height;

			PxClothParticle* vertices = new PxClothParticle[(width + 1)*(height + 1) * 4];
			PxU32* quads = new PxU32[width*height * 4];

			for (PxU32 j = 0; j < (height + 1); j++)
			{
				for (PxU32 i = 0; i < (width + 1); i++)
				{
					PxU32 offset = i + j * (width + 1);
					vertices[offset].pos = PxVec3(w_step*i, 0.f, h_step*j);
					if (fix_top && (j == 0)) //fix the top row of vertices
						vertices[offset].invWeight = 0.f;
					else
						vertices[offset].invWeight = 1.f;
				}

				for (PxU32 j = 0; j < height; j++)
				{
					for (PxU32 i = 0; i < width; i++)
					{
						PxU32 offset = (i + j * width) * 4;
						quads[offset + 0] = (i + 0) + (j + 0)*(width + 1);
						quads[offset + 1] = (i + 1) + (j + 0)*(width + 1);
						quads[offset + 2] = (i + 1) + (j + 1)*(width + 1);
						quads[offset + 3] = (i + 0) + (j + 1)*(width + 1);
					}
				}
			}

			//init cloth mesh description
			mesh_desc.points.data = vertices;
			mesh_desc.points.count = (width + 1)*(height + 1);
			mesh_desc.points.stride = sizeof(PxClothParticle);

			mesh_desc.invMasses.data = &vertices->invWeight;
			mesh_desc.invMasses.count = (width + 1)*(height + 1);
			mesh_desc.invMasses.stride = sizeof(PxClothParticle);

			mesh_desc.quads.data = quads;
			mesh_desc.quads.count = width * height;
			mesh_desc.quads.stride = sizeof(PxU32) * 4;

			//create cloth fabric (cooking)
			PxClothFabric* fabric = PxClothFabricCreate(*GetPhysics(), mesh_desc, PxVec3(0, -1, 0));

			//create cloth
			actor = (PxActor*)GetPhysics()->createCloth(pose, *fabric, vertices, PxClothFlags());
			//collisions with the scene objects
			((PxCloth*)actor)->setClothFlag(PxClothFlag::eSCENE_COLLISION, true);

			colors.push_back(default_color);
			actor->userData = new UserData(&colors.back(), &mesh_desc);
		}

		~Cloth()
		{
			delete (UserData*)actor->userData;
		}
	};
}