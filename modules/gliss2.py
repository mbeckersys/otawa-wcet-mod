# gliss module builder
from buildlib import *

def get(path, env, pack):
	return Module(
		name = "gliss2",
		path = path,
		env = env,
		package = pack,
		downloader = MercurialDownloader("https://anon:anon@www.irit.fr/hg/TRACES/gliss2/trunk"),
		maker = MakeMaker(nojob = True),
		local = True,
		uses = [ "thot" ]
	)
