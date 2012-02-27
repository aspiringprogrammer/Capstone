//#include "ExampleApplication.h"
//#include <math.h>
//
//
//class Example1FrameListener : public Ogre::FrameListener
//{
//private:
//	Ogre::SceneNode* _node;
//	Ogre::SceneNode* _ninjanode;
//	OIS::InputManager* _man;
//	OIS::Keyboard* _key;
//	OIS::Mouse* _mouse;
//	Ogre::Camera* _Cam;
//	Ogre::Entity* _ent;
//	Ogre::Entity* _ninja;
//	Ogre::AnimationState* _aniState;
//	Ogre::AnimationState* _aniStateTop;
//	Ogre::AnimationState* _ninjaAni;
//	Ogre::Vector3 SinbadTranslate;
//
//
//public: Example1FrameListener(Ogre::Entity* ent, Ogre::SceneNode* node,Ogre::Entity* ninja, Ogre::SceneNode* ninjanode, Ogre::Entity* ents[], RenderWindow* win, Ogre::Camera* cam)
//		{
//			SinbadTranslate = Ogre::Vector3(0,0,0);
//			_ninja = ninja;
//			_ninjanode = ninjanode;
//			_ent = ent;
//			_node = node;
//			_ninjaAni = _ninja->getAnimationState("Idle1");
//			_ninjaAni->setEnabled(true);
//			_ninjaAni->setLoop(true);
//			// retrieve a certain animation state "amuse" and enable it:
//			_aniState = _ent->getAnimationState("IdleBase");
//			_aniState->setEnabled(true);
//			_aniState->setLoop(true);
//
//			_aniStateTop = _ent->getAnimationState("IdleTop");
//			_aniStateTop->setEnabled(true);
//			_aniStateTop->setLoop(true);
//
//
//			_Cam = cam;
//			// handle the window data
//			size_t windowHnd = 0;
//			std::stringstream windowHndStr;
//			// Ask for the window handle
//			win->getCustomAttribute("WINDOW", &windowHnd);
//			// Convert to string
//			windowHndStr << windowHnd;
//			// Create a parameter list for OIS and add window handle
//			OIS::ParamList pl;
//			pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
//			// Create input system
//			_man = OIS::InputManager::createInputSystem(pl);
//			// Create keyboard to check for user input
//			_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false));
//			// Create mouse to check for movement or clicking
//			_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse, false));
//		}
//
//		bool frameStarted(const Ogre::FrameEvent &evt)
//		{
//			//animation state variable needs to know how much time has elapsed since its last update
//			_aniState->addTime(evt.timeSinceLastFrame);
//			_aniStateTop->addTime(evt.timeSinceLastFrame);
//			_ninjaAni->addTime(evt.timeSinceLastFrame);
//			// check for key presses
//			_key->capture();
//			// escape game
//			if(_key->isKeyDown(OIS::KC_ESCAPE)){
//				// close window
//				return false;
//			}
//			// check for mouse movement or clicks
//			_mouse->capture();
//
//
//			float fCameraTranslationSpeed = 6.0;
//			float fCameraRotation  = 1.0;
//			//Turn the mouse movement into an angle to rotate the camera
//			// Process mouse relative movement into an angle
//			float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
//			float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
//
//			//Process keyboard input into camera translation:
//			Ogre::Vector3 translate(0, 0, 0);
//			if(_key->isKeyDown(OIS::KC_W)){
//				translate += Ogre::Vector3(0, 0, -fCameraTranslationSpeed);
//			}
//			if(_key->isKeyDown(OIS::KC_S)){
//				translate += Ogre::Vector3(0, 0, fCameraTranslationSpeed);
//			}
//			if(_key->isKeyDown(OIS::KC_A)){
//				translate += Ogre::Vector3(-fCameraTranslationSpeed, 0, 0);
//			}
//			if(_key->isKeyDown(OIS::KC_D)){
//				translate += Ogre::Vector3(fCameraTranslationSpeed, 0, 0);
//			}
//
//			translate *= fCameraTranslationSpeed;
//			rotX *= fCameraRotation;
//			rotY *= fCameraRotation;
//
//			// Translate camera using translate vector
//			_Cam->moveRelative(translate * evt.timeSinceLastFrame);
//
//			bool walked = false;
//
//			if(_key->isKeyDown(OIS::KC_UP))
//			{
//			SinbadTranslate = Ogre::Vector3(0,0,-1);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_DOWN))
//			{
//			SinbadTranslate = Ogre::Vector3(0,0,1);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_LEFT))
//			{
//			SinbadTranslate = Ogre::Vector3(-1,0,0);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_RIGHT))
//			{
//			SinbadTranslate = Ogre::Vector3(1,0,0);
//			walked = true;
//			}
//
//			bool attacked = false;
//
//			if(_key->isKeyDown(OIS::KC_X))
//			{
//			attacked = true;
//			}
//
//
//			if(attacked)
//			{
//				_aniStateTop = _ent->getAnimationState("SliceHorizontal");
//				_aniStateTop->setEnabled(true);			
//				_aniState->setLoop(false);
//				_aniStateTop->setLoop(false);
//				if(_aniStateTop->hasEnded())
//				{
//					_aniStateTop->setTimePosition(0.0f);
//				}
//				float distanceX = abs(_ninjanode->getPosition().x-_node->getPosition().x);
//				float distanceZ = abs(_ninjanode->getPosition().z-_node->getPosition().z);
//				if(distanceX <= 7.0 && distanceZ <= 7.0)
//				{
//					//not sure why my ninja doesn't fall all the way to the ground, must assume it is something with my machine.
//					_ninjaAni = _ninja->getAnimationState("Death1");
//					_ninjaAni->setEnabled(true);
//					_ninjaAni->setLoop(false);
//				}
//			}
//			else if(walked){
//				_aniState = _ent->getAnimationState("RunBase");
//				_aniStateTop = _ent->getAnimationState("RunTop");
//				_node->translate(SinbadTranslate * evt.timeSinceLastFrame * 12.0f);
//				_aniState->setEnabled(true);
//				_aniStateTop->setEnabled(true);
//				_aniState->setLoop(false);
//				_aniStateTop->setLoop(false);
//				if(_aniState->hasEnded())
//				{
//					_aniState->setTimePosition(0.0f);
//				}
//				if(_aniStateTop->hasEnded())
//				{
//					_aniStateTop->setTimePosition(0.0f);
//				}
//			}
//			else
//			{
//				_aniState = _ent->getAnimationState("IdleBase");
//				_aniStateTop = _ent->getAnimationState("IdleTop");
//				_aniState->setEnabled(true);
//				_aniStateTop->setEnabled(true);
//				_aniState->setLoop(true);
//				_aniStateTop->setLoop(true);
//				//_aniState->setTimePosition(0.0f);
//				//_aniStateTop->setTimePosition(0.0f);
//			}
//			
//			if(_ninjaAni->hasEnded())
//				{
//			
//				}
//			_node->resetOrientation();
//			Ogre::Quaternion qOrientation(1, 0, 0, 0);
//			Vector3 src = Vector3::UNIT_Z;
//			qOrientation = src.getRotationTo(SinbadTranslate);
//			_node->rotate(qOrientation);
//
//			// Find the local x and y axes
//			Ogre::Vector3 localYAxis;
//			Ogre::Vector3 localXAxis;
//
//			// multiply the camera's quaternion by the up and right vectors
//			// to get the x and y axes shifted by the camera's orientation
//			localYAxis = Vector3::UNIT_Y; 
//			localXAxis = _Cam->getOrientation() * Vector3::UNIT_X; 
//
//			// Create our quaternions that represent yaw and pitch
//			Ogre::Quaternion quatYaw(Ogre::Radian(rotX), localYAxis);	Ogre::Quaternion quatPitch(Ogre::Radian(rotY), localXAxis);
//
//			// Combine qaw and pitch by multiplying the two quaternions
//			Ogre::Quaternion quat = quatYaw * quatPitch;
//
//			// Rotate the camera by our quaternion
//			_Cam->rotate(quat);
//
//
//			return true;
//		}
//
//};
//
//
//class Example1 : public ExampleApplication
//{
//private:
//	Ogre::Entity* _Sinbad;
//	Ogre::Entity* Ninja;
//	Ogre::SceneNode* _SinbadNode;
//	Ogre::SceneNode* _NinjaNode;
//	Ogre::Entity* ents[4];
//public:
//
//
//	void createCamera()
//	{
//		mCamera = mSceneMgr->createCamera("MyCamera1");
//		mCamera->setPosition(0, 100, 200);
//		mCamera->lookAt(0,0,0);
//		mCamera->setNearClipDistance(5);
//
//	}
//
//	// Add movement to the scene
//	void createFrameListener(){
//		Ogre::FrameListener* FrameListener = new Example1FrameListener(_Sinbad, _SinbadNode,Ninja,_NinjaNode, ents, mWindow, mCamera);
//		mRoot->addFrameListener(FrameListener);
//
//	}
//
//
//	void createScene()
//	{
//		Ogre::Entity* swordEntity;
//		Ogre::Entity* swordEntity2;
//		swordEntity = mSceneMgr->createEntity("sword.mesh");
//		swordEntity2 = mSceneMgr->createEntity("sword.mesh");
//		Ogre::Plane plane(Vector3::UNIT_Y, -5);
//		Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
//		Ogre::Entity* entPlane = mSceneMgr->createEntity("LightPlaneEntity", "plane");
//		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlane);
//		mSceneMgr->setSkyDome(true,"Examples/CloudySky");
//		entPlane->setMaterialName("Examples/GrassFloor");
//		// Add light to scene
//		Ogre::Light* light = mSceneMgr->createLight("Light1");
//		light->setType(Ogre::Light::LT_DIRECTIONAL);
//		light->setDirection(Ogre::Vector3(1, -1, 0));
//
//		Ogre::Entity* ent[4];
//		Ogre::SceneNode* node[4];  
//
//		Ninja = mSceneMgr->createEntity("ninja.mesh");
//		_NinjaNode = mSceneMgr->createSceneNode();
//		mSceneMgr->getRootSceneNode()->addChild(_NinjaNode);
//		_NinjaNode->attachObject(Ninja);
//		_NinjaNode->scale(0.05,0.05,0.05);
//		_NinjaNode->translate(1,-5,7);
//
//		_Sinbad = mSceneMgr->createEntity("Sinbad.mesh");
//		_Sinbad->attachObjectToBone("Handle.L",swordEntity);
//		_Sinbad->attachObjectToBone("Handle.R",swordEntity2);
//		_SinbadNode = mSceneMgr->createSceneNode();
//		mSceneMgr->getRootSceneNode()->addChild(_SinbadNode);
//		_SinbadNode->attachObject(_Sinbad);
//		//_SinbadNode->scale(0.4,0.4,0.4);
//		//_SinbadNode->setPosition(0,4,0);
//
//
//		//Orientate the Houses
//		for(int i = 0; i < 4; i++) {
//			ents[i] = ent[i] = mSceneMgr->createEntity("tudorhouse.mesh");
//			node[i] = mSceneMgr->createSceneNode();
//			mSceneMgr->getRootSceneNode()->addChild(node[i]);
//			node[i]->attachObject(ent[i]);
//			node[i]->scale(0.05,0.05,0.05);
//			
//			if (i%2 == 0){
//				node[i]->setOrientation(45*i,0,1,0);
//				node[i]->translate(0, 22, -80, Ogre::Node::TS_LOCAL);
//			}
//			else{
//				node[i]->setOrientation(180,0,1,0);
//				node[i]->translate(80, 22, 0, Ogre::Node::TS_LOCAL);
//			}
//		}
//		//manually mess with the other two, I wasted more time on doing the other parts so thats why this is hard coded.
//		node[1]->yaw(Ogre::Radian(3.14f+1.5f));
//		node[3]->translate(-160,0,0,Ogre::Node::TS_LOCAL);
//		node[3]->yaw(Ogre::Radian(1.5f));
//	}
//};
//
//int main (void)
//{
//	Example1 app;
//	app.go();
//	return 0;
//}
