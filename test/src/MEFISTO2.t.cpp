#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs_ShapeEnum.hxx>

#include <SMESH_Gen.hxx>
#include <SMESH_Mesh.hxx>
#include <StdMeshers_LocalLength.hxx>
#include <StdMeshers_Regular_1D.hxx>
#include <StdMeshers_MEFISTO_2D.hxx>
#include <StdMeshers_QuadranglePreference.hxx>

TEST_CASE("Mesh the faces of a box.", "[MEFISTO2][Box]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(true);

	StdMeshers_LocalLength* hyp1d = new StdMeshers_LocalLength(0, gen);
	hyp1d->SetLength(1.0);
	StdMeshers_Regular_1D* algo1d = new StdMeshers_Regular_1D(1, gen);

	StdMeshers_QuadranglePreference* hyp2d = new StdMeshers_QuadranglePreference(2, gen);
	StdMeshers_MEFISTO_2D* algo2d = new StdMeshers_MEFISTO_2D(3, gen);

	mesh->ShapeToMesh(box);
	mesh->AddHypothesis(box, 0);
	mesh->AddHypothesis(box, 1);
	mesh->AddHypothesis(box, 2);
	mesh->AddHypothesis(box, 3);

	bool success = gen->Compute(*mesh, box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbNodes() == 1244);
	REQUIRE(mesh->NbTriangles() == 2484);
	REQUIRE(mesh->NbQuadrangles() == 0);

	delete hyp1d;
	delete algo1d;
	delete hyp2d;
	delete algo2d;
	delete mesh;
	delete gen;
}
