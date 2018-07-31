# Create and set custom vertex colors on a polygon object

import pymel.core as pm     # PyMel commands

poly = pm.PyNode('pSphere1|pSphereShape1')

try:
    pm.nt.Mesh(poly)
    print ">> mesh:", poly.name()

except TypeError:
    print "Not a mesh"

allColorSets = poly.getColorSetNames()
print ">> color sets:", allColorSets

# number of per-face per-vertex colors
numColors = poly.numColors()
print ">> color count:", numColors

# create new empty color set
if not 'myCustomColors' in allColorSets:
    myColorSet = poly.createColorSet(colorSetName='myCustomColors')
else:
    poly.setCurrentColorSetName(setName='myCustomColors')

# iterate through vertices to set color, slowest
for i, vtx in enumerate(poly.verts):
    nrm = poly.getVertexNormal(i, angleWeighted=False) # averaged normal per global vertex
    print(nrm, pm.datatypes.Color(nrm))
    poly.setVertexColor(pm.datatypes.Color(nrm), i)
