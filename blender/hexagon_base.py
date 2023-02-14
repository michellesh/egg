import bpy


def create_mesh_obj(verts, edges, faces, name="mesh"):
    mesh_data = bpy.data.meshes.new(name + "_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new(name, mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj


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


add_cube(name='Cubey', dimensions=(3, 4, 5), location=(0, 0, 45))
add_cylinder(name='Cindy', radius=5, depth=7, location=(0, 0, 35), rotation=(45, 0, 0))
