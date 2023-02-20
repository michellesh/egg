import bpy
from math import radians


def create_mesh_obj(verts, edges, faces, name="mesh"):
    mesh_data = bpy.data.meshes.new(name + "_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new(name, mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj

def add_cube(name='Cube', dimensions=(0, 0, 0), **kwargs):
    bpy.ops.mesh.primitive_cube_add(**kwargs)
    obj = bpy.context.object
    obj.name = name
    obj.data.name = name + '_data'
    obj.dimensions = dimensions

def add_cylinder(name='Cylinder', **kwargs):
    bpy.ops.mesh.primitive_cylinder_add(**kwargs)
    obj = bpy.context.object
    obj.name = name
    obj.data.name = name + '_data'


#name = 'Hexagon'
#verts = [
#    # top
#    (25.75, -24.86, 24.92),    #0
#    (-25.75, -24.86, 24.92),    #1
#    (-40.21, 9.96, 24.92),    #2
#    (-20.1, 44.78, 24.92),    #3
#    (20.1, 44.78, 24.92),    #4
#    (40.21, 9.96, 24.92),    #5
#    # middle
#    (45.56, -51.64, -10.30),    #6
#    (-45.56, -51.64, -10.30),    #7
#    (-62.33, 13.77, -10.30),    #8
#    (-31.16, 67.75, -10.30),    #9
#    (31.16, 67.75, -10.30),    #10
#    (62.33, 13.77, -10.30),    #11
#    # bottom
#    (45.55, -51.62, -16.75),    #12
#    (-45.55, -51.62, -16.75),    #13
#    (-62.32, 13.77, -16.75),    #14
#    (-31.16, 67.74, -16.75),    #15
#    (31.16, 67.74, -16.75),    #16
#    (62.32, 13.77, -16.75),    #17
#]
#edges = []
#faces = [
#    (0, 1, 2, 3, 4, 5),
#    (0, 1, 7, 6),
#    (1, 2, 8, 7),
#    (2, 3, 9, 8),
#    (3, 4, 10, 9),
#    (4, 5, 11, 10),
#    (5, 0, 6, 11),
#    (6, 7, 13, 12),
#    (7, 8, 14, 13),
#    (8, 9, 15, 14),
#    (9, 10, 16, 15),
#    (10, 11, 17, 16),
#    (11, 6, 12, 17),
#    (12, 13, 14, 15, 16, 17),
#]
#create_mesh_obj(verts, edges, faces, name=name)

# Main access hole in the bottom of the hexagon
#name = 'HexagonBottomHole'
#verts = [
#    # bottom
#    (-38.84, -42.51, -19.70),    #0
#    (38.84, -42.51, -19.70),    #1
#    (53.14, 13.14, -19.70),    #2
#    (26.57, 59.27, -19.70),    #3
#    (-26.57, 59.27, -19.70),    #4
#    (-53.14, 13.24, -19.70),    #5
#    # top
#    (-38.84, -42.51, -9.70),    #6
#    (38.84, -42.51, -9.70),    #7
#    (53.14, 13.14, -9.70),    #8
#    (26.57, 59.27, -9.70),    #9
#    (-26.57, 59.27, -9.70),    #10
#    (-53.14, 13.24, -9.70),    #11
#]
#edges = []
#faces = [(0, 1, 2, 3, 4, 5), (6, 7, 8, 9, 10, 11), (0, 1, 7, 6), (1, 2, 8, 7),
#         (2, 3, 9, 8), (3, 4, 10, 9), (4, 5, 11, 10), (5, 0, 6, 11)]
#create_mesh_obj(verts, edges, faces, name=name)


## Hexagon Holes: Back
#add_cube(name='Hexagon.Diff.OnOffSwitch', dimensions=(18.5, 13, 4), location=(0, 52.89, 11.96), rotation=(radians(-56.25), 0, 0))
#add_cylinder(name='Hexagon.Diff.PowerCable', radius=3.5, depth=4, location=(0, 57, -1.5), rotation=(radians(-56.25), 0, 0))
#
## Hexagon Holes: Top
#add_cylinder(name='Hexagon.Diff.SwivelKnob', radius=3.5, depth=5, location=(0, 9.96, 24.31))
#add_cylinder(name='Hexagon.Diff.MicroUsb', radius=6, depth=30, location=(-18, 9.96, 12), rotation=(0, 0, radians(5.625)))
#add_cylinder(name='Hexagon.MicroUsbTunnel', radius=8.5, depth=22, location=(-18, 9.96, 12.668), rotation=(0, 0, radians(5.625)))
## Move the inner half toward center: gx 6
#
## Hexagon Holes: Front
#add_cylinder(name='Hexagon.Diff.Knob1', radius=3.5, depth=5, location=(-15, -40.91, 2.85), rotation=(radians(52.43), 0, 0))
#add_cube(name='Hexagon.Diff.KnobTab1', dimensions=(2, 1, 2), location=(-15, -43.75, -2.6), rotation=(radians(52.43), 0, 0))
#add_cylinder(name='Hexagon.Diff.Knob2', radius=3.5, depth=5, location=(15, -40.91, 2.85), rotation=(radians(52.43), 0, 0))
#add_cube(name='Hexagon.Diff.KnobTab2', dimensions=(2, 1, 2), location=(15, -43.75, -2.6), rotation=(radians(52.43), 0, 0))
#
## Hexagon Tabs
#add_cylinder(name='Hexagon.Tab1', radius=4, depth=2, location=(-40, -48, -15))
#add_cylinder(name='Hexagon.Tab2', radius=4, depth=2, location=(40, -48, -15))
#add_cylinder(name='Hexagon.Tab3', radius=4, depth=2, location=(27, 58, -15))
#add_cylinder(name='Hexagon.Tab4', radius=4, depth=2, location=(-27, 58, -15))



#add_cube(name='Hole', dimensions=(x, y, z), location=(x, y, z))
#add_cylinder(name='Hole', radius=r, depth=d, location=(x, y, z))
