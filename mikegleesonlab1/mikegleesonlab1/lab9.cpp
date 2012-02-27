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
//		Ogre::SceneNode* _CamNode;
//		Ogre::Entity* _ent;
//		Ogre::AnimationState* _aniState;
//		Ogre::AnimationState* _aniStateTop;
//		Ogre::Vector3 SinbadTranslate;
//
//
//public: Example1FrameListener(Ogre::Entity* ent, Ogre::SceneNode* node, RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* camNode)
//	{
//	SinbadTranslate = Ogre::Vector3::ZERO;
//	_ent = ent;
//	_node = node;
//	_CamNode = camNode;
//	// retrieve a certain animation state "Dance" and enable it:
//	_aniState = _ent->getAnimationState("Dance");
//	_aniStateTop = _ent->getAnimationState("RunTop");
//	_aniState->setEnabled(true);
//	_aniState->setLoop(true);
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
//			SinbadTranslate = Ogre::Vector3(0, 0, 0);
//			bool walked = false;
//
//			if(_key->isKeyDown(OIS::KC_UP))
//			{
//				if(SinbadTranslate.z < 1)
//				SinbadTranslate += Ogre::Vector3(0,0,1);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_DOWN))
//			{
//				if(SinbadTranslate.z > -1)
//				SinbadTranslate += Ogre::Vector3(0,0,-1);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_LEFT))
//			{
//				if(SinbadTranslate.x < 1)
//				SinbadTranslate += Ogre::Vector3(1,0,0);
//			walked = true;
//			}
//			if(_key->isKeyDown(OIS::KC_RIGHT))
//			{
//				if(SinbadTranslate.x > -1)
//				SinbadTranslate += Ogre::Vector3(-1,0,0);
//			walked = true;
//			}
//
//			if(walked){
//				Ogre::Vector3 mCameraDistance = Ogre::Vector3(0.0f, 5.0f, -15.0f);
//
//				_CamNode->setPosition(_node->getPosition() + mCameraDistance);
//				_Cam->lookAt(_node->getPosition());
//
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
//
//			if(walked)
//			{
//			_node->resetOrientation();
//			Ogre::Quaternion qOrientation(1, 0, 0, 0);
//			Vector3 src = Vector3::UNIT_Z;
//			qOrientation = src.getRotationTo(SinbadTranslate);
//			_node->rotate(qOrientation);
//			}
//	
//			//translate *= fCameraTranslationSpeed;
//			rotX *= fCameraRotation;
//			rotY *= fCameraRotation;
//
//			// Translate camera using translate vector
//			//_Cam->moveRelative(SinbadTranslate * evt.timeSinceLastFrame);
//
//			//_node->setPosition()
//	
//			// Rotate using Euler angles and rotation speed
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
//			//_Cam->rotate(quat);
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
//		Ogre::SceneNode* _CamNode;
//public:
//
//
//void createCamera()
//{
//	mCamera = mSceneMgr->createCamera("MyCamera1");
//	_CamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CameraNode");
//	_CamNode->attachObject(mCamera);
//	mCamera->setPosition(0, 5, -15);
//	mCamera->lookAt(0,0,0);
//	mCamera->setNearClipDistance(5);
//
//}
//
//// Add movement to the scene
//void createFrameListener(){
//	Ogre::FrameListener* FrameListener = new Example1FrameListener(_SinbadEnt, _SinbadNode, mWindow, mCamera, _CamNode);
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
//	mSceneMgr->setSkyDome(true,"Examples/CloudySky");
//
//
//	_SinbadEnt = mSceneMgr->createEntity("Sinbad.mesh");
//	_SinbadNode = mSceneMgr->createSceneNode();
//	mSceneMgr->getRootSceneNode()->addChild(_SinbadNode);
//	_SinbadNode->attachObject(_SinbadEnt);
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
