import os
import shutil

def moveSDL2windowDLL():
	current = os.getcwd()

	#If a newer version exists in the visual studio
	#project, then copy it into the DLL_Files folder
	vsDLLpath = os.path.join(current, "SDL2window", "vs2010_project", "Release", "sdl2window.dll")
	storedDLLpath = os.path.join(current, "DLL_Files", "sdl2window.dll")
	if os.path.isfile(vsDLLpath):
		if os.path.getmtime(vsDLLpath) > os.path.getmtime(storedDLLpath):
			shutil.copy(vsDLLpath, storedDLLpath)

	#Get unity's root directory, assuming
	#This file is somewhere in Unity's Assets directory
	unityRoot = current
	while not (os.path.basename(unityRoot) in ("", "Assets")):
		unityRoot = os.path.dirname(unityRoot)
	unityRoot = os.path.dirname(unityRoot)
	if os.path.basename(unityRoot) == "":
		print "Warning: Not in Unity Assets directory"
		return

	#Copy SDL2.dll to unity's root
	SDL2path = os.path.join(unityRoot, "SDL2.dll")
	if not os.path.isfile(SDL2path):
		shutil.copy(os.path.join(current, "DLL_Files", "SDL2.dll"), SDL2path)

	#Copy sdl2window.dll to the plugins folder
	pluginPath = os.path.join(unityRoot, "Assets", "Plugins")
	if not os.path.isfile(pluginPath):
		os.makedirs(pluginPath)

	pluginDllPath = os.path.join(unityRoot, "Assets", "Plugins", "sdl2window.dll")
	if not os.path.isfile(pluginDllPath) or \
		os.path.getmtime(storedDLLpath) > os.path.getmtime(pluginDllPath):
		shutil.copy(storedDLLpath, pluginDllPath)

if __name__ == "__main__":
	moveSDL2windowDLL()