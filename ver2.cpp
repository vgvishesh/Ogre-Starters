#include "Ogre\Ogre.h"

class MyApp
{
private:
	Ogre::SceneManager* _mSceneMgr;
	Ogre::Root* _root;
public:
	MyApp()
	{
		_mSceneMgr=NULL;
		_root=NULL;
	}

	~MyApp()
	{
		delete _root;
	}

	void loadResources()
	{
		Ogre::ConfigFile cf;
		cf.load("resources_d.cfg");
		Ogre::ConfigFile::SectionIterator secItr=cf.getSectionIterator();
		Ogre::String sectionName,typeName, dataname;
		while(secItr.hasMoreElements())
		{
			sectionName=secItr.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings=secItr.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for(i=settings->begin();i!=settings->end();++i)
			{
				typeName=i->first;
				dataname=i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataname,typeName,sectionName);
			}
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void createScene()
	{
		Ogre::Entity* ent=_mSceneMgr->createEntity("ent","sinbad.mesh");
		_mSceneMgr->getRootSceneNode()->attachObject(ent);
	}

	int startup()
	{
		_root=new Ogre::Root("plugins_d.cfg");
		if(!_root->showConfigDialog())
		{
			return -1;
		}
		
		Ogre::RenderWindow* window=_root->initialise(true,"Ogre Vishesh");
		_mSceneMgr = _root->createSceneManager(Ogre::ST_GENERIC);
		Ogre::Camera* camera=_mSceneMgr->createCamera("Camera");
		camera->setPosition(Ogre::Vector3(0,0,50));
		camera->lookAt(0,0,0);
		camera->setNearClipDistance(5);

		Ogre::Viewport* vp=window->addViewport(camera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
		camera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));

		loadResources();
		createScene();		
		_root->startRendering();
		return 0;
	}		
};



int main()
{
	MyApp A;
	A.startup();
	return 0;
}


