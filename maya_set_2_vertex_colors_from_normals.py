# Create and set custom vertex colors on a polygon object
# We create two new colorsets,
# (1) with the "shared" vertex normal
# (2) with the face normal set on all face-vertices

import pymel.core as pm     # PyMel commands

poly = pm.PyNode('pSphere1|pSphereShape1')

try:
    pm.nt.Mesh(poly)
    print ">> mesh:", poly.name()

except TypeError:
    print "Not a mesh"

allColorSets = poly.getColorSetNames()
print ">> color sets:", allColorSets

# (1) set color from shared normal at each polygon vertex

# create new empty custom color set
if not 'mySharedNormal' in allColorSets:
    poly.createColorSet(colorSetName='mySharedNormal')

# set current color set
poly.setCurrentColorSetName(setName='mySharedNormal')

# iterate through vertices to set color, slowest
for i, vtx in enumerate(poly.verts):
    nrm = poly.getVertexNormal(i, angleWeighted=False) # averaged normal per global vertex
    print(nrm, pm.datatypes.Color(nrm))
    poly.setVertexColor(pm.datatypes.Color(nrm), i) # set color on all faces the vertex belongs to

# (2) set color from face normal at each face vertex

# create new empty custom color set
if not 'myFaceNormal' in allColorSets:
    poly.createColorSet(colorSetName='myFaceNormal')

# set current color set
poly.setCurrentColorSetName(setName='myFaceNormal')

# iterate through faces to set color, slowest
for i, vtx in enumerate(poly.faces):
    nrm = poly.getPolygonNormal(i, space='object') # face normal
    print(nrm, pm.datatypes.Color(nrm))
    poly.setFaceColor(pm.datatypes.Color(nrm), i) # set color on all vertices of the face
