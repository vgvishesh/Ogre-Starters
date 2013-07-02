#include "Ogre\Ogre.h"


int main(void)
{
	Ogre::Root* root=new Ogre::Root("plugins_d.cfg");
	if(!root->showConfigDialog())
	{
		return -1;
	}

	Ogre::RenderWindow* window=root->initialise(true,"Ogre Vishesh");
	Ogre::SceneManager* sceneManager = root->createSceneManager(Ogre::ST_GENERIC);
	Ogre::Camera* camera=sceneManager->createCamera("Camera");
	camera->setPosition(Ogre::Vector3(0,0,50));
	camera->lookAt(0,0,0);
	camera->setNearClipDistance(5);

	Ogre::Viewport* vp=window->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
	
	//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media/packs/Sinbad.zip","Zip");
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
	Ogre::Entity* ent=sceneManager->createEntity("ent","sinbad.mesh");

	sceneManager->getRootSceneNode()->attachObject(ent);
	
	root->startRendering();

	
	return 0;
}


