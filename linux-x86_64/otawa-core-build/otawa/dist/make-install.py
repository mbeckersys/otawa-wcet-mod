#!/usr/bin/python
#
# This script requires SIS sources to be installed (at the same level
# as OTAWA sources).

import os
import re
import stat

map = {
	"APP":		"OTAWA",
	"DB_URL":	"http://tracesgroup.net/otawa/packages/1.0",
	"DB_CONF":	"share/Otawa/install.xml"
}
path = "otawa-install.py"

out = open(path, "w")
for line in open("../../sis/sis-install.py").readlines():
	m = re.match(r"^([A-Z_]+)\s*=\s*\"", line)
	if m and map.has_key(m.group(1)):
		out.write("%s = \"%s\"\n" % (m.group(1), map[m.group(1)]))
	else:
		out.write(line)

os.chmod(path, stat.S_IXUSR | os.stat(path).st_mode)
