#include "SMESH_Gen.hxx"
#include "SMESH_Mesh.hxx"
#include "SMESH_MesherHelper.hxx"
#include "SMESHDS_Mesh.hxx"
int main()
{
    SMESH_Gen gen;
    gen.CreateMesh(1, true);
    SMESH_Mesh* mesh = gen.CreateMesh(1, true);
    SMESH_MesherHelper helper(*mesh);
    SMESHDS_Mesh* meshDS = mesh->GetMeshDS();
    SMDS_MeshNodePtr n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    n1 = meshDS->AddNode(6, 12, 18);
    n2 = meshDS->AddNode(0, 0, 18);
    n3 = meshDS->AddNode(12, 0, 18);
    n4 = meshDS->AddNode(6, 6, 0);
    n5 = meshDS->AddNode(3, 6, 18);
    n6 = meshDS->AddNode(6, 0, 18);
    n7 = meshDS->AddNode(9, 6, 18);
    n8 = meshDS->AddNode(6, 9, 9);
    n9 = meshDS->AddNode(3, 3, 9);
    n10 = meshDS->AddNode(9, 3, 9);
    meshDS->AddVolumeWithID(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, 1);
    mesh->ExportUNV("/tmp/test.unv");
}