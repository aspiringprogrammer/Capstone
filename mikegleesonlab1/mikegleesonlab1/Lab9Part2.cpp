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
//		Ogre::Vector3 mCameraDistance;
//		float fCameraRotation;
//
//public: Example1FrameListener(Ogre::Entity* ent, Ogre::SceneNode* node, RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* camNode)
//	{
//	mCameraDistance = Ogre::Vector3(0,5,-15);
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
//			fCameraRotation = 0.0;
//			//Turn the mouse movement into an angle to rotate the camera
//			// Process mouse relative movement into an angle
//			float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
//			float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
//
//			//Process keyboard input into camera translation:
//			SinbadTranslate = Ogre::Vector3(0, 0, 0);
//			bool walked = false;
//			bool mCameraRotate = false;
//				// cameraRotateValue is how much the camera rotates in degrees per second
//			if(_key->isKeyDown(OIS::KC_Q)) {
//				fCameraRotation += 240.0f * evt.timeSinceLastFrame;
//				mCameraRotate = true;
//			}
//			if (_key->isKeyDown(OIS::KC_E)) {
//				fCameraRotation -= 240.0f * evt.timeSinceLastFrame;
//				mCameraRotate = true;
//			}
//
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
//			if (mCameraRotate) {
//				// Create the rotation matrix
//				Ogre::Matrix3 rotYMatrix = Ogre::Matrix3();
//				rotYMatrix.FromAxisAngle(Ogre::Vector3::UNIT_Y, Ogre::Degree(fCameraRotation));
//				// Update the distance vector
//				mCameraDistance = rotYMatrix * mCameraDistance;
//
//				// Change the orientation of mCameraNode so that our movement
//				// code will still work properly
//				_CamNode->yaw(Ogre::Degree(fCameraRotation), Ogre::Node::TS_LOCAL);
//
//				_CamNode->setPosition(_node->getPosition() + mCameraDistance);
//				_Cam->lookAt(_node->getPosition());
//			}
//
//
//
//			if(walked){
//				Ogre::Vector3 goalDirection = Ogre::Vector3::ZERO;
//				goalDirection += SinbadTranslate.z * _CamNode->getOrientation().zAxis();
//				goalDirection += SinbadTranslate.x * _CamNode->getOrientation().xAxis();
//				goalDirection.normalise();
//
//				
//				Ogre::Quaternion goalQuat = _node->getOrientation().zAxis().getRotationTo(goalDirection);
//
//				Ogre::Real yawToGoal = goalQuat.getYaw().valueDegrees();
//	
//				// Limit how fast Sinbad turns
//				// turnSpeed is a variable like runningSpeed that controls how fast
//				// Sinbad turns in degrees per second.
//				Ogre::Real yawAtSpeed =yawToGoal / Ogre::Math::Abs(yawToGoal)* 500.0 * evt.timeSinceLastFrame;
//				if (yawToGoal < 0)
//					yawToGoal = std::min<Ogre::Real>(
//					0, std::max<Ogre::Real>(yawToGoal, yawAtSpeed));
//				else if (yawToGoal > 0) 
//					yawToGoal = std::max<Ogre::Real>(
//					0, std::min<Ogre::Real>(yawToGoal, yawAtSpeed));
//
//
//				_CamNode->setPosition(_node->getPosition() + mCameraDistance);
//				_Cam->lookAt(_node->getPosition());
//
//								// Now we can rotate and translate Sinbad
//				_node->yaw(Ogre::Degree(yawToGoal));
//				// Because Sinbad is rotating to move in the goal direction, we don’t need
//				// to move him on the x axis, only the z axis
//				_node->translate(0, 0, 2.0 * evt.timeSinceLastFrame,
//					Ogre::Node::TS_LOCAL);
//
//				// Remember to fix the camera’s position
//				_CamNode->setPosition(_node->getPosition() + mCameraDistance);
//				_Cam->lookAt(_node->getPosition());
//
//				_aniState = _ent->getAnimationState("RunBase");
//				//_node->translate(SinbadTranslate * evt.timeSinceLastFrame * 12.0f);
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