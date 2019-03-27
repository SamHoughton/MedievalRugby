#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(51.f/255.f,35.f/255.f,0.f/255.f),PxVec3(102.f/255.f,102.f/255.f,102.f/255.f),PxVec3(21.f/255.f,0.f/255.f,168.f/255.f), PxVec3(0.f/255.f ,209.f/255.f, 111.f/255.f), PxVec3(255.f / 255.f ,255.f / 255.f, 255.f / 255.f), PxVec3(127.f / 255.f ,119.f / 255.f, 102.f / 255.f), PxVec3(25.f / 255.f ,19.f / 255.f, 0.f / 255.f) };

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2),
			ACTOR3		= (1 << 3),
			ACTOR4		= (1 << 4),
			//add more if you need
		};
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;

		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
	public:
		Plane* plane;
		Bottom* bottom, * bottom2;
		Top* top, *top2;
		Capsule* sphere1;
		Goal* goal1;
		Horse* horse;
		catapult* catapultBase;
		catapultarm* catapultArm;
		DistanceJoint* joint, *joint2;
		RevoluteJoint* joint3;
		PxMaterial* ballMaterial;
		MySimulationEventCallback* my_callback;
		Cloth* cloth, *banner1, *banner2, *flagPart1, *flagPart2;
		castle* castleLeft, *castleRight;
		halfwayLine* halfwayline;
		Wall* wallLeft, *wallRight;
		backWall* backwall;
		HiddenBox* hiddenbox;
		Flag* flag1, *flag2;
	

		MyScene() : Scene() {};

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			plane = new Plane();
			plane->Color(color_palette[5]);
			Add(plane);

			bottom = new Bottom(PxTransform(PxVec3(.0f,.5f,30.0f)));
			bottom->Color(color_palette[6]);
			
			hiddenbox = new HiddenBox(PxTransform(PxVec3(25.f, 10.f, 0.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
			hiddenbox->Color(color_palette[6]);
			Add(hiddenbox);
			
			wallRight = new Wall(PxTransform(PxVec3(.0f,6.f,32.0f)));
			wallRight->Color(color_palette[7]);
			Add(wallRight);
			
			wallLeft = new Wall(PxTransform(PxVec3(.0f,6.f,-32.5f)));
			wallLeft->Color(color_palette[7]);
			Add(wallLeft);
			
			backwall = new backWall(PxTransform(PxVec3(35.0f, 5.5f, 0.f)));
			backwall->Color(color_palette[7]);
			Add(backwall);

			bottom2 = new Bottom(PxTransform(PxVec3(.0f, .5f, -30.0f)));
			bottom2->Color(color_palette[6]);
			
			top = new Top(PxTransform(PxVec3(30.0f, 0.5f, 0.0f)));
			top->Color(color_palette[6]);

			sphere1 = new Capsule(PxTransform(PxVec3(.5f, 2.f, 2.f)));
			sphere1->Color(color_palette[0]);
			sphere1->SetupFiltering(FilterGroup::ACTOR3, FilterGroup::ACTOR4);


			goal1 = new Goal(PxTransform(PxVec3(15.f, 0.f, 0.f), PxQuat(PxPiDivTwo, PxVec3(0.f,1.f,0.f))));
			goal1->Color(color_palette[4]);

			catapultBase = new catapult(PxTransform(PxVec3(-15.f, 2.f, 0.f)));
			catapultBase->Color(color_palette[2]);			
			
			catapultArm = new catapultarm(PxTransform(PxVec3(-15.f, 6.5f, 0.f)));
			catapultArm->Color(color_palette[8]);

			cloth = new Cloth(PxTransform(PxVec3(16.f, 20.f, 5.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec2(10.f, 15.f), 10, 10);
			cloth->Color(color_palette[6]);
			Add(cloth);
			
			banner1 = new Cloth(PxTransform(PxVec3(32.0f, 9.f, 25.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec2(5.f, 8.f), 10, 10);
			banner1->Color(color_palette[1]);
			Add(banner1);
			
			banner2 = new Cloth(PxTransform(PxVec3(32.0f, 9.f, -20.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec2(5.f, 8.f), 10, 10);
			banner2->Color(color_palette[1]);
			Add(banner2);
			//cloth->SetupFiltering(FilterGroup::ACTOR4, FilterGroup::ACTOR3);
			
			castleLeft = new castle(PxTransform(PxVec3(38.f, 5.f, 35.f)));
			castleLeft->Color(color_palette[7]);
			Add(castleLeft);
			
			castleRight = new castle(PxTransform(PxVec3(38.f, 5.f, -35.f)));
			castleRight->Color(color_palette[7]);
			Add(castleRight);
			
			flag1 = new Flag(PxTransform(PxVec3(38.f, 18.f, -35.f)));
			flag1->Color(color_palette[7]);
			Add(flag1);
			
			flag2 = new Flag(PxTransform(PxVec3(38.f, 25.f, 35.f)));
			flag2->Color(color_palette[7]);
			Add(flag2);

			//set collision filter flags
			bottom->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);

			bottom2->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);

			top->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);
			
			plane->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR1);
			
			hiddenbox->SetupFiltering(FilterGroup::ACTOR3, FilterGroup::ACTOR4);
			
			sphere1->SetupFiltering(FilterGroup::ACTOR4, FilterGroup::ACTOR3);
			
			
			Add(bottom);
			Add(bottom2);
			Add(top);
			Add(goal1);
			Add(catapultBase);
			Add(catapultArm);


			joint = new DistanceJoint(bottom, PxTransform(PxVec3(0.f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), top, PxTransform(PxVec3(0.f, 5.f, 0.f)));

			joint2 = new DistanceJoint(bottom2, PxTransform(PxVec3(0.f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), top, PxTransform(PxVec3(0.f, 5.f, 0.f)));

			joint3 = new RevoluteJoint(catapultBase, PxTransform(PxVec3(2.f, 2.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), catapultArm, PxTransform(PxVec3(0.f, 0.f, 0.f)));

			ballMaterial = CreateMaterial(0.5f, 0.2f, 0.597);

			int RandX;
			int RandY;
			int RandColour;

			for (int a = 0; a < 20; a = a + 1) {
			
				RandX = rand() % 20;
				RandY = rand() % 80 + -40;
				RandColour = rand() % 8;

				horse = new Horse(PxTransform(PxVec3(RandX, 1.f, RandY), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
				Add(horse);
				horse->Color(color_palette[RandColour]);

				PxActor* horseActor = horse->Get();
				if (horseActor->isRigidBody())
				{
					PxRigidBody* horseBody = (PxRigidBody*)horseActor;

					horseBody->addForce(PxVec3(RandY, 0.0f, RandX), PxForceMode::eIMPULSE, 1);
				}
			}

		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{



		}

		void AbnormalCase(){
			int RandX;
			int RandY;
			int RandColour;

			for (int a = 0; a < 20; a = a + 1) {

				RandX = rand() % 20;
				RandY = rand() % 80 + -40;
				RandColour = rand() % 8;

				horse = new Horse(PxTransform(PxVec3(RandX, 1.f, RandY), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
				Add(horse);
				horse->Color(color_palette[RandColour]);

				PxActor* horseActor = horse->Get();
				if (horseActor->isRigidBody())
				{
					PxRigidBody* horseBody = (PxRigidBody*)horseActor;

					horseBody->addForce(PxVec3(RandY, 0.0f, RandX), PxForceMode::eIMPULSE, 1);
				}
			}
		}

		void shotGun() 
		{
			int i = 0;
			int x = 0;
			
				PxActor* GunActor = catapultBase->Get();

				if (GunActor->isRigidBody()) {
					
					PxRigidBody* rigidbodyGun = (PxRigidBody*)GunActor;
					PxTransform gunPose = rigidbodyGun->getGlobalPose();

					sphere1 = new Capsule(PxTransform(gunPose));
					sphere1->Color(color_palette[2]);
					sphere1->Material(ballMaterial);
					Add(sphere1);
				}

				PxActor* BallActor = sphere1->Get();																

			if (BallActor->isRigidBody())
			{
				//actor is 100% a rigidbody
				//..

				PxRigidBody* rigidbodyBall = (PxRigidBody*)BallActor;


				float Px = 2;
				float Py = 1;

				//add some forces
				rigidbodyBall ->addForce(PxVec3(Px, Py, .0f), PxForceMode::eIMPULSE, 1);
				rigidbodyBall ->addForce(PxVec3(Px, Py, .0f), PxForceMode::eIMPULSE, 1);
			}

				x++;
				i++;

			
			//PxRigidBody::addForce(PxVec3)

			//PxRigidBody::addForce(*(PxRigidDynamic*)sphere1, 1.0f);
		}

		void StartGame()
		{
					
			
		}

		// Movement
		void ForceRight() {
			PxActor* base = catapultBase->Get();
			if (base->isRigidBody())
			{
				PxRigidBody* baseBody = (PxRigidBody*)base;

				baseBody->addForce(PxVec3(0.f, 0.0f, 15.f), PxForceMode::eIMPULSE, 1);
			}
		}
		void ForceLeft() {
			PxActor* base = catapultBase->Get();
			if (base->isRigidBody())
			{
				PxRigidBody* baseBody = (PxRigidBody*)base;

				baseBody->addForce(PxVec3(0.f, 0.0f, -25.f), PxForceMode::eIMPULSE, 1);
			}
		}
	};
}
