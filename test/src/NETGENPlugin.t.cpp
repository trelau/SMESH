#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <BRepAlgoAPI_Splitter.hxx>
#include <TopTools_ListOfShape.hxx>

#include <SMESH_Gen.hxx>
#include <SMESH_Mesh.hxx>
#include <SMESH_Hypothesis.hxx>
#include <NETGENPlugin_SimpleHypothesis_2D.hxx>
#include <NETGENPlugin_SimpleHypothesis_3D.hxx>
#include <NETGENPlugin_NETGEN_2D.hxx>
#include <NETGENPlugin_NETGEN_2D3D.hxx>
#include <StdMeshers_LocalLength.hxx>
#include <StdMeshers_Regular_1D.hxx>

TEST_CASE("Mesh a box with tetrahedral elements.", "[NETGENPlugin]") {

    TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

    SMESH_Gen* gen = new SMESH_Gen();
    SMESH_Mesh* mesh = gen->CreateMesh(true);

    NETGENPlugin_SimpleHypothesis_3D* hyp = new NETGENPlugin_SimpleHypothesis_3D(0, gen);
    hyp->SetLocalLength(1.0);

    NETGENPlugin_NETGEN_2D3D* algo = new NETGENPlugin_NETGEN_2D3D(1, gen);

    mesh->ShapeToMesh(box);
    mesh->AddHypothesis(box, 0);
    mesh->AddHypothesis(box, 1);

    bool success = gen->Compute(*mesh, box);
    REQUIRE(success == true);

    REQUIRE(mesh->NbTetras() == 5087);
    REQUIRE(mesh->NbNodes() == 1243);

    delete hyp;
    delete algo;
    delete mesh;
    delete gen;
}

TEST_CASE("Mesh a box with tetrahedral elements and a local edge length.", "[NETGENPlugin]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	TopExp_Explorer exp = TopExp_Explorer(box, TopAbs_EDGE);
	const TopoDS_Shape& edge = exp.Current();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(true);

	NETGENPlugin_SimpleHypothesis_3D* hyp3d = new NETGENPlugin_SimpleHypothesis_3D(0, gen);
	hyp3d->SetLocalLength(1.0);
	NETGENPlugin_NETGEN_2D3D* algo3d = new NETGENPlugin_NETGEN_2D3D(1, gen);

	StdMeshers_LocalLength* hyp1d = new StdMeshers_LocalLength(2, gen);
	hyp1d->SetLength(0.1);
	StdMeshers_Regular_1D* algo1d = new StdMeshers_Regular_1D(3, gen);

	mesh->ShapeToMesh(box);
	mesh->AddHypothesis(box, 0);
	mesh->AddHypothesis(box, 1);
	mesh->AddHypothesis(edge, 2);
	mesh->AddHypothesis(edge, 3);

	bool success = gen->Compute(*mesh, box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbTetras() == 36831);
	REQUIRE(mesh->NbNodes() == 7240);

	delete hyp3d;
	delete algo3d;
	delete hyp1d;
	delete algo1d;
	delete mesh;
	delete gen;
}

TEST_CASE("Mesh a box with tetrahedral elements and split faces.", "[NETGENPlugin]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	gp_Pnt origin = gp_Pnt(5.0, 0.0, 0.0);
	gp_Dir normal = gp_Dir(1.0, 0.0, 0.0);
	gp_Pln pln = gp_Pln(origin, normal);

	TopoDS_Face face = BRepBuilderAPI_MakeFace(pln, -5.0, 5.0, -5.0, 5.0).Face();

	TopTools_ListOfShape args = TopTools_ListOfShape();
	args.Append(box);

	TopTools_ListOfShape tools = TopTools_ListOfShape();
	tools.Append(face);

	BRepAlgoAPI_Splitter splitter = BRepAlgoAPI_Splitter();
	splitter.SetArguments(args);
	splitter.SetTools(tools);
	splitter.Build();
	REQUIRE(splitter.IsDone() == true);

	TopoDS_Shape split_box = splitter.Shape();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(true);

	NETGENPlugin_SimpleHypothesis_3D* hyp = new NETGENPlugin_SimpleHypothesis_3D(0, gen);
	hyp->SetLocalLength(1.0);

	NETGENPlugin_NETGEN_2D3D* algo = new NETGENPlugin_NETGEN_2D3D(1, gen);

	mesh->ShapeToMesh(split_box);
	mesh->AddHypothesis(split_box, 0);
	mesh->AddHypothesis(split_box, 1);

	bool success = gen->Compute(*mesh, split_box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbTetras() == 4905);
	REQUIRE(mesh->NbNodes() == 1215);

	delete hyp;
	delete algo;
	delete mesh;
	delete gen;
}

TEST_CASE("Mesh a box with quadrilateral elements and split faces.", "[NETGENPlugin]") {

	TopoDS_Solid box = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Solid();

	gp_Pnt origin = gp_Pnt(5.0, 0.0, 0.0);
	gp_Dir normal = gp_Dir(1.0, 0.0, 0.0);
	gp_Pln pln = gp_Pln(origin, normal);

	TopoDS_Face face = BRepBuilderAPI_MakeFace(pln, -5.0, 5.0, -5.0, 5.0).Face();

	TopTools_ListOfShape args = TopTools_ListOfShape();
	args.Append(box);

	TopTools_ListOfShape tools = TopTools_ListOfShape();
	tools.Append(face);

	BRepAlgoAPI_Splitter splitter = BRepAlgoAPI_Splitter();
	splitter.SetArguments(args);
	splitter.SetTools(tools);
	splitter.Build();
	REQUIRE(splitter.IsDone() == true);

	TopoDS_Shape split_box = splitter.Shape();

	SMESH_Gen* gen = new SMESH_Gen();
	SMESH_Mesh* mesh = gen->CreateMesh(true);

	NETGENPlugin_SimpleHypothesis_2D* hyp = new NETGENPlugin_SimpleHypothesis_2D(0, gen);
	hyp->SetLocalLength(1.0);
	hyp->SetAllowQuadrangles(true);

	NETGENPlugin_NETGEN_2D* algo = new NETGENPlugin_NETGEN_2D(1, gen);

	mesh->ShapeToMesh(split_box);
	mesh->AddHypothesis(split_box, 0);
	mesh->AddHypothesis(split_box, 1);

	bool success = gen->Compute(*mesh, split_box);
	REQUIRE(success == true);

	REQUIRE(mesh->NbFaces() == 625);
	REQUIRE(mesh->NbTriangles() == 0);
	REQUIRE(mesh->NbQuadrangles() == 625);
	REQUIRE(mesh->NbNodes() == 627);

	delete hyp;
	delete algo;
	delete mesh;
	delete gen;
}