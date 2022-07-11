#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs_ShapeEnum.hxx>

#include <SMESH_Gen.hxx>
#include <SMESH_Mesh.hxx>
#include <SMESH_Hypothesis.hxx>
#include <StdMeshers_LocalLength.hxx>
#include <StdMeshers_Regular_1D.hxx>

TEST_CASE("Mesh an edge of a box.", "[StdMeshers][LocalLength]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	TopExp_Explorer exp = TopExp_Explorer(box, TopAbs_EDGE);
	const TopoDS_Shape& edge = exp.Current();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(true);

	StdMeshers_LocalLength* hyp1d = new StdMeshers_LocalLength(0, gen);
	hyp1d->SetLength(0.1);
	StdMeshers_Regular_1D* algo1d = new StdMeshers_Regular_1D(1, gen);

	mesh->ShapeToMesh(box);
	mesh->AddHypothesis(edge, 0);
	mesh->AddHypothesis(edge, 1);

	bool success = gen->Compute(*mesh, box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbNodes() == 107);

	delete hyp1d;
	delete algo1d;
	delete mesh;
	delete gen;
}
