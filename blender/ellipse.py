import bpy
import math


def create_mesh_obj(verts, edges, faces, name="mesh"):
    mesh_data = bpy.data.meshes.new(name + "_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new(name, mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj


# values pasted from output of angles_in_ellipse function
x = [
    0.0, 19.164128756480789, 37.961362486083111, 55.942107121885087,
    72.457505846506791, 86.472747433283701, 96.344018749077748, 100.0,
    96.344018749077748, 86.472747433283701, 72.457505846506777,
    55.942107121885073, 37.961362486083083, 19.164128756480768,
    1.2246467991473532e-14, -19.164128756480789, -37.961362486083104,
    -55.942107121885066, -72.457505846506791, -86.472747433283743,
    -96.344018749077748, -100.0, -96.344018749077776, -86.472747433283715,
    -72.457505846506848, -55.942107121885087, -37.961362486083097,
    -19.164128756480736
]
y = [
    70.0, 68.702552520357372, 64.760158504423842, 58.021853804184261,
    48.243712800599027, 35.156895997177685, 18.754645427890768,
    4.2862637970157365e-15, -18.754645427890775, -35.156895997177678,
    -48.243712800599035, -58.021853804184268, -64.760158504423842,
    -68.702552520357372, -70.0, -68.702552520357372, -64.760158504423842,
    -58.021853804184275, -48.243712800599035, -35.156895997177635,
    -18.754645427890775, -1.2858791391047208e-14, 18.754645427890694,
    35.156895997177671, 48.243712800598992, 58.021853804184261,
    64.760158504423842, 68.702552520357372
]

num_rings = 13
verts = [(x[i], 0, y[i]) for i in range(len(x))]
edges = []
faces = []

obj = create_mesh_obj(verts, edges, faces, name="ellipse")
obj.rotation_euler = (0, math.radians(90), 0)