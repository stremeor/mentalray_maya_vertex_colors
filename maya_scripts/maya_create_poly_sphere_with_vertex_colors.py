# Create and set custom vertex colors on a polygon object
# We create a poly sphere, then add two new colorsets,
# (1) with the "shared" vertex normal
# (2) with the face normal set on all face-vertices

import pymel.core as pm     # PyMel commands

object = pm.polySphere(name='myPolySphere')

poly = pm.PyNode(object[0]).getShape()

try:
    pm.nodetypes.Mesh(poly)
    print ">> mesh:", poly.name()

except TypeError:
    print "Not a mesh"

allColorSets = poly.getColorSetNames()
print ">> color sets, before:", allColorSets

# (1) set color from shared normal at each polygon vertex

colorSet = 'mySharedNormal'

print ">> create color set:", colorSet

# create new empty custom color set
if not colorSet in allColorSets:
    poly.createColorSet(colorSetName=colorSet)

# set current color set
poly.setCurrentColorSetName(setName=colorSet)

print ">> fill color set:",colorSet

# iterate through vertices to set color, slowest
for i, vtx in enumerate(poly.verts):
    nrm = poly.getVertexNormal(i, angleWeighted=False) # averaged normal per global vertex
    print(nrm, pm.datatypes.Color(nrm))
    poly.setVertexColor(pm.datatypes.Color(nrm), i) # set color on all faces the vertex belongs to

# (2) set color from face normal at each face vertex

colorSet = 'myFaceNormal'

print ">> create color set:", colorSet

# create new empty custom color set
if not colorSet in allColorSets:
    poly.createColorSet(colorSetName=colorSet)

# set current color set
poly.setCurrentColorSetName(setName=colorSet)

print ">> fill color set:",colorSet

# iterate through faces to set color, slowest
for i, vtx in enumerate(poly.faces):
    nrm = poly.getPolygonNormal(i, space='object') # face normal
    print(nrm, pm.datatypes.Color(nrm))
    poly.setFaceColor(pm.datatypes.Color(nrm), i) # set color on all vertices of the face

allColorSets = poly.getColorSetNames()
print ">> color sets, after:", allColorSets
