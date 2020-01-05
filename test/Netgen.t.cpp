#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>

#include <SMESH_Gen.hxx>
#include <SMESH_Mesh.hxx>
#include <SMESH_Hypothesis.hxx>
#include <NETGENPlugin_SimpleHypothesis_3D.hxx>
#include <NETGENPlugin_NETGEN_2D3D.hxx>

TEST_CASE("Mesh a box with tetrahedral elements.", "[netgen][solid]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(0, true);

	NETGENPlugin_SimpleHypothesis_3D* hyp = new NETGENPlugin_SimpleHypothesis_3D(0, 0, gen);
	hyp->SetLocalLength(1.0);

	NETGENPlugin_NETGEN_2D3D* algo = new NETGENPlugin_NETGEN_2D3D(1, 0, gen);

	mesh->ShapeToMesh(box);
	mesh->AddHypothesis(box, 0);
	mesh->AddHypothesis(box, 1);

	bool success = gen->Compute(*mesh, box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbTetras() == 4767);
	REQUIRE(mesh->NbNodes() == 1189);

	delete hyp;
	delete algo;
	delete mesh;
	delete gen;
}