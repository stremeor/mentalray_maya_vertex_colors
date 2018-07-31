# mentalray_maya_vertex_colors
## Create custom vertex colors in Maya and read them in a mentalray shader.

This is a **Mental Ray for Maya** example that demonstrates how to access
custom vertex color data stored on Maya's mesh geometry from a mentalray shader.

As an example, execute the Python script for Maya (actually using PyMEL)
that creates a poly sphere and attaches 2 new color sets, and fills them
with the normals found on the same vertex. Any floating point data triple
can be stored instead, of course. Alternatively, in a real production,
vertex colors may be painted directly by artists inside Maya.

The **Mental Ray for Maya** plugin fully translates this custom vertex data.
A custom mentalray shader can search for the "data block" that the plugin
generates upon translation/file export, and grab the information about
size / offset of vertex colors in a certain set. That is needed to properly
address the vertex color data in mentalray's vertex data list of the mesh.

There is also a **.mi** file for testing. It is a plain export from Maya with
the custom shader added next to the material shader of the poly object,
to just print out the information about a specific "named" color set.
Should be self explanatory.

BTW, the shader code can be used for any kind of data block in a mentalray
**.mi** file scene.

Here are some links to related **Mental Ray for Maya** online help topics

[Render color per vertex in mentalray for Maya](https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2016/ENU/Maya/files/GUID-6ED598A1-86DD-4B2C-B34A-25BB13C979ED-htm.html)

[mentalray for Maya custom shaders](https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2016/ENU/Maya/files/GUID-4F5F2A6F-55B5-47EE-BBD1-69F99C5BE4A6-htm.html)

[mentalray custom vertex data](https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2016/ENU/Maya/files/GUID-1C2282A6-B524-45C4-B050-4369FA13F5E0-htm.html)
