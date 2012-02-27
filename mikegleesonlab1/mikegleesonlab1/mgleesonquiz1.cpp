//#include "ExampleApplication.h"
//
//
//class Example1FrameListener : public Ogre::FrameListener
//{
//private:
//	Ogre::SceneNode* _node;
//	OIS::InputManager* _man;
//	OIS::Keyboard* _key;
//	OIS::Mouse* _mouse;
//	Ogre::Camera* _Cam;
//	Ogre::Entity* _ent;
//	Ogre::AnimationState* _aniState;
//
//
//public: Example1FrameListener(Ogre::Entity* ent, Ogre::SceneNode* node, Ogre::Entity* ents[], RenderWindow* win, Ogre::Camera* cam)
//		{
//
//			_ent = ent;
//			_node = node;
//			// retrieve a certain animation state "amuse" and enable it:
//			_aniState = _ent->getAnimationState("amuse");
//			_aniState->setEnabled(true);
//			_aniState->setLoop(true);
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
//
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
//private:
//	Ogre::Entity* _Penguin;
//	Ogre::SceneNode* _PenguinNode;
//	Ogre::Entity* ents[3];
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
//		Ogre::FrameListener* FrameListener = new Example1FrameListener(_Penguin, _PenguinNode, ents, mWindow, mCamera);
//		mRoot->addFrameListener(FrameListener);
//
//	}
//
//
//	void createScene()
//	{
//		Ogre::Plane plane(Vector3::UNIT_Y, -5);
//		Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 200, 200, true, 1, 5, 5, Vector3::UNIT_Z);
//		Ogre::Entity* entPlane = mSceneMgr->createEntity("LightPlaneEntity", "plane");
//		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlane);
//		entPlane->setMaterialName("Examples/GrassFloor");
//		// Add light to scene
//		Ogre::Light* light = mSceneMgr->createLight("Light1");
//		light->setType(Ogre::Light::LT_DIRECTIONAL);
//		light->setDirection(Ogre::Vector3(1, -1, 0));
//
//		Ogre::Entity* ent[3];
//		Ogre::Entity* penguin;
//		Ogre::SceneNode* pnode;
//		Ogre::SceneNode* node[3];  
//
//		_Penguin = penguin = mSceneMgr->createEntity("penguin.mesh");
//		_PenguinNode = pnode = mSceneMgr->createSceneNode();
//		mSceneMgr->getRootSceneNode()->addChild(pnode);
//		pnode->attachObject(penguin);
//		pnode->scale(0.4,0.4,0.4);
//		pnode->setPosition(0,4,0);
//
//		for(int i = 0; i < 3; i++) {
//			ents[i] = ent[i] = mSceneMgr->createEntity("tudorhouse.mesh");
//			node[i] = mSceneMgr->createSceneNode();
//			mSceneMgr->getRootSceneNode()->addChild(node[i]);
//			node[i]->attachObject(ent[i]);
//			node[i]->scale(0.1,0.1,0.1);
//			//node[i]->yaw(Ogre::Degree(45*i));
//			node[i]->translate(90*i, 50, -80, Ogre::Node::TS_LOCAL);
//			//node[i]->setOrientation(135,0,50,-80);
//		}
//		node[1]->translate(0,0,60);
//		node[2]->translate(-90*3,0,60);
//		node[1]->yaw(Ogre::Degree(-45));
//		node[2]->yaw(Ogre::Degree(45));
//	}
//};
//
//int main (void)
//{
//	Example1 app;
//	app.go();
//	return 0;
//}
