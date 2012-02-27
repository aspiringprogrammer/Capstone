//#include "ExampleApplication.h"
//
//
//class Example1FrameListener : public Ogre::FrameListener
//{
//	private:
//		Ogre::SceneNode* _node;
//		OIS::InputManager* _man;
//		OIS::Keyboard* _key;
//		OIS::Mouse* _mouse;
//		Ogre::Camera* _Cam;
//		Ogre::Entity* _ent;
//		Ogre::AnimationState* _aniState;
//		Ogre::AnimationState* _aniStateTop;
//		Ogre::AnimationState* _aniStates[20];
//		Ogre::Vector3 SinbadTranslate;
//
//
//public: Example1FrameListener(Ogre::Entity* ent, Ogre::SceneNode* node, Ogre::Entity* ents[], RenderWindow* win, Ogre::Camera* cam)
//	{
//	SinbadTranslate = Ogre::Vector3::ZERO;
//	_ent = ent;
//	_node = node;
//	// retrieve a certain animation state "Dance" and enable it:
//	_aniState = _ent->getAnimationState("Dance");
//	_aniStateTop = _ent->getAnimationState("RunTop");
//	_aniState->setEnabled(true);
//	_aniState->setLoop(true);
//
//	for(int i = 0; i < 10; i++)
//	{
//		_aniStates[i] = ents[i]->getAnimationState("RunBase");
//		_aniStates[i]->setEnabled(true);
//		_aniStates[i]->setLoop(true);
//		_aniStates[i+10] = ents[i]->getAnimationState("RunTop");
//		_aniStates[i+10]->setEnabled(true);
//		_aniStates[i+10]->setLoop(true);
//	}
//
//
//	_Cam = cam;
//	// handle the window data
//	size_t windowHnd = 0;
//	std::stringstream windowHndStr;
//	// Ask for the window handle
//	win->getCustomAttribute("WINDOW", &windowHnd);
//	// Convert to string
//	windowHndStr << windowHnd;
//	// Create a parameter list for OIS and add window handle
//	OIS::ParamList pl;
//	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
//	// Create input system
//	_man = OIS::InputManager::createInputSystem(pl);
//	// Create keyboard to check for user input
//	_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false));
//	// Create mouse to check for movement or clicking
//	_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse, false));
//	}
//
//	bool frameStarted(const Ogre::FrameEvent &evt)
//		{
//			//animation state variable needs to know how much time has elapsed since its last update
//			_aniState->addTime(evt.timeSinceLastFrame);
//			for(int i = 0; i < 10; i++){
//				_aniStates[i]->addTime(evt.timeSinceLastFrame);
//				_aniStates[i+10]->addTime(evt.timeSinceLastFrame);
//			}
//
//			// check for key presses
//		_key->capture();
//		// escape game
//			if(_key->isKeyDown(OIS::KC_ESCAPE)){
//				// close window
//			return false;
//		}
//			// check for mouse movement or clicks
//			_mouse->capture();
//
//
//			float fCameraTranslationSpeed = 20.0;
//			float fCameraRotation  = 1.0;
//			//Turn the mouse movement into an angle to rotate the camera
//			// Process mouse relative movement into an angle
//			float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
//			float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
//
//			//Process keyboard input into camera translation:
//			Ogre::Vector3 translate(0, 0, 0);
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
//			if(walked){
//				_aniState = _ent->getAnimationState("RunBase");
//				_node->translate(SinbadTranslate * evt.timeSinceLastFrame * 12.0f);
//				_aniState->setEnabled(true);
//				_aniStateTop->setEnabled(true);
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
//				_aniState->setTimePosition(0.0f);
//				_aniState->setEnabled(false);	
//				_aniStateTop->setTimePosition(0.0f);
//				_aniStateTop->setEnabled(false);
//			}
//			_node->resetOrientation();
//			Ogre::Quaternion qOrientation(1, 0, 0, 0);
//			Vector3 src = Vector3::UNIT_Z;
//			qOrientation = src.getRotationTo(SinbadTranslate);
//			_node->rotate(qOrientation);
//
//	
//			translate *= fCameraTranslationSpeed;
//			rotX *= fCameraRotation;
//			rotY *= fCameraRotation;
//
//			// Translate camera using translate vector
//			_Cam->moveRelative(SinbadTranslate * evt.timeSinceLastFrame);
//
//			//_node->setPosition()
//	
//			// Rotate using Euler angles and rotation speed
//			//_Cam->yaw(Ogre::Radian(rotX * fCameraRotation));
//			//_Cam->pitch(Ogre::Radian(rotY * fCameraRotation));
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
//		private:
//		Ogre::Entity* _SinbadEnt;
//		Ogre::SceneNode* _SinbadNode;
//		Ogre::Entity* ents[11];
//public:
//
//
//void createCamera()
//{
//	mCamera = mSceneMgr->createCamera("MyCamera1");
//	mCamera->setPosition(0, 100, 200);
//	mCamera->lookAt(0,0,0);
//	mCamera->setNearClipDistance(5);
//
//}
//
//// Add movement to the scene
//void createFrameListener(){
//	Ogre::FrameListener* FrameListener = new Example1FrameListener(_SinbadEnt, _SinbadNode, ents, mWindow, mCamera);
//	mRoot->addFrameListener(FrameListener);
//
//}
//
//
//void createScene()
//{
//	Ogre::Plane plane(Vector3::UNIT_Y, -5);
//	Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
//	Ogre::Entity* entPlane = mSceneMgr->createEntity("LightPlaneEntity", "plane");
//	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlane);
//	entPlane->setMaterialName("Examples/BeachStones");
//	// Add light to scene
//	Ogre::Light* light = mSceneMgr->createLight("Light1");
//	light->setType(Ogre::Light::LT_DIRECTIONAL);
//	light->setDirection(Ogre::Vector3(1, -1, 0));
//
//	Ogre::Entity* ent[11];
//	Ogre::SceneNode* node[11];  
//	
//	
//	for(int i = 0; i < 10; i++) {
//		ents[i] = ent[i] = mSceneMgr->createEntity("Sinbad.mesh");
//		node[i] = mSceneMgr->createSceneNode();
//		mSceneMgr->getRootSceneNode()->addChild(node[i]);
//		node[i]->attachObject(ent[i]);
//		//This was the line of sinbads
//		//node[i]->setPosition(-10*i,0,0);
//		/* Second circle picture 
//		node[i]->yaw(Ogre::Degree(i*45));
//		node[i]->translate(0, 0, 20, Ogre::Node::TS_LOCAL);
//		*/
//		/* Third Weird Picture 
//		node[i]->translate(0,0,20, Ogre::Node::TS_LOCAL);
//		node[i]->yaw(Ogre::Degree(45*i));
//		*/
//		node[i]->yaw(Ogre::Degree(36*i));
//		node[i]->translate(0, 0, 20, Ogre::Node::TS_LOCAL);
//		node[i]->yaw(Ogre::Degree(-90));
//		
//	}
//
//	_SinbadEnt = ent[10] = mSceneMgr->createEntity("Sinbad.mesh");
//	_SinbadNode = node[10] = mSceneMgr->createSceneNode();
//	 //node[10]->createChildSceneNode("Node1");
//	mSceneMgr->getRootSceneNode()->addChild(node[10]);
//	_SinbadNode->attachObject(ent[10]);
//	/* LAB 1 & 2 */
//
//	/*
//Ogre::Entity* ent =
//		mSceneMgr->createEntity("MyEntity","Sinbad.mesh");
////mSceneMgr->getRootSceneNode()->attachObject(ent);
//Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
//mSceneMgr->getRootSceneNode()->addChild(node);
//node->attachObject(ent);
//
//Quaternion q1(0.71, 0, 0.71, 0);
//Quaternion q2(0.71, 0.71, 0, 0);
//Quaternion q3(0.71, 0, 0, 0.71);
//
//node->setPosition(-15,0,450);
//
//Ogre::Entity* ent2 = mSceneMgr->createEntity("MyEntity2", "Sinbad.mesh");
//Ogre::SceneNode* node2 = mSceneMgr->createSceneNode("Node2");
//node->addChild(node2);
//node2->attachObject(ent2);
//node2->translate(10, 0, 0);
//node2->rotate(q1);
////node2->yaw(Ogre::Degree(90.0f));
//
//Ogre::Entity* ent3 = mSceneMgr->createEntity("MyEntity3", "Sinbad.mesh");
//Ogre::SceneNode* node3 = mSceneMgr->createSceneNode("Node3");
//node->addChild(node3);
//node3->attachObject(ent3);
//node3->translate(20, 0, 0);
//node3->rotate(q2);
////node3->pitch(Ogre::Degree(90.0f));
//
//Ogre::Entity* ent4 = mSceneMgr->createEntity("MyEntity4", "Sinbad.mesh");
//Ogre::SceneNode* node4 = mSceneMgr->createSceneNode("Node4");
//node->addChild(node4);
//node4->attachObject(ent4);
//node4->translate(30, 0, 0);
//node4->rotate(q3);
////node4->roll(Ogre::Degree(90.0f));
//
//Ogre::Entity* ent5 = mSceneMgr->createEntity("MyEntity5", "Sinbad.mesh");
//Ogre::SceneNode* node5 = mSceneMgr->createSceneNode("Node5");
//node->addChild(node5);
//node5->attachObject(ent5);
//node5->translate(15, 0, -15);
//node5->setScale(7, 7, 7);
//*/
//}
//
//
//};
//
//int main (void)
//{
//	Example1 app;
//	app.go();
//	return 0;
//}
