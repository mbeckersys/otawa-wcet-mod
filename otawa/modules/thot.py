# thot module builder
from buildlib import *

def get(path, env, pack):
	return Module(
		name = "thot",
		path = path,
		env = env,
		package = pack,
		downloader = GitDownloader("https://github.com/hcasse/Thot.git"),
		maker = MakeMaker(nojob = True),
		local = True
	)
