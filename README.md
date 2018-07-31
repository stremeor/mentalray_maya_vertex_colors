# mentalray_maya_vertex_colors
Create custom vertex colors in Maya and read them in a mentalray shader.

This is a Mental Ray for Maya example that demonstrates how to access
custom vertex color data stored on Maya's mesh geometry from a MR shader.

As an example, execute the Python script for Maya (actually using PyMEL)
that creates a poly sphere and attaches 2 new color sets, and fills them
with the normals found on the same vertex. Any floating point data triple
can be stored instead, of course. Alternatively, in a real production,
vertex colors may be painted directly by artists inside Maya.

The Mental Ray for Maya plugin fully translates this custom vertex data.
A custom mentalray shader can search for the "data block" that the plugin
generates upon translation/file export, and grab the information about
size / offset of vertex colors in a certain set. That is needed to properly
address the vertex color data in mentalray's vertex data list of the mesh.

There is also .mi file for testing. It is a plain export from Maya with
the custom shader added next to the material shader of the poly object,
to just print out the information about a specific "named" color set.
Should be self explanatory.

BTW, the shader code can be used for any kind of data block in a .mi scene.
