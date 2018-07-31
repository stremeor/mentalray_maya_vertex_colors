# mentalray_maya_vertex_colors
Create custom vertex colors in Maya and read them in a mentalray shader.

This is a Mental Ray for Maya example that demonstrates how to access
custom vertex color data stored on Maya's mesh geometry from a MR shader.

To run the example, execute the Python script for Maya (actually using PyMEL)
that creates a poly sphere and attaches 2 new color sets, and fills them
with the normals found on the same vertex. Any floating point data triple
can be stored instead, of course.

The custom mentalray shader searches for the data block that Mental Ray for Maya
plugin generates upon translation/file export, to grab the information
about size and offset of the vertex colors in a certain set.

There is also .mi file for testing. It is a plain export from Maya with
the custom shader added next to the material shader of the poly object,
to just print out the information about a specific "named" color set.
Should be self explanatory.

BTW, the shader code can be used for any kind of data block in a .mi scene.
