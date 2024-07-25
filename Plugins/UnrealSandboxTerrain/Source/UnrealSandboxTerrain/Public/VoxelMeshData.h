#pragma once

#include "EngineMinimal.h"
#include "VoxelData.h"
#include "Mesh.h"

#include <list>
#include <array>
#include <memory>
#include <set>
#include <mutex>
#include <functional>

extern std::atomic<int> md_counter;
extern std::atomic<int> cd_counter;

// translate set of material id to uint64 code
union TTransitionMaterialCode {

	uint16 TriangleMatId[4];

	uint64 Code;
};

// mesh per one material
typedef struct TMeshMaterialSection {

	unsigned short MaterialId = 0;

	FProcMeshSection MaterialMesh;

	int32 vertexIndexCounter = 0;

} TMeshMaterialSection;

typedef struct TMeshMaterialTransitionSection : TMeshMaterialSection {
	uint64 TransitionCode;
	std::set<unsigned short> MaterialIdSet;

	static uint64 GenerateTransitionCode(const std::set<unsigned short>& MaterialIdSet) {
		TTransitionMaterialCode TransMat;
		for (int i = 0; i < 4; i++) { 
			TransMat.TriangleMatId[i] = 0; //TODO incorrect material
		}

		int i = 0;
		for (unsigned short MaterialId : MaterialIdSet) {
			TransMat.TriangleMatId[i] = MaterialId;
			i++; 
			if (i == 4) break;
		}

		return TransMat.Code;
	}

} TMeshMaterialTransitionSection;


typedef TMap<unsigned short, TMeshMaterialSection> TMaterialSectionMap;
typedef TMap<unsigned short, TMeshMaterialTransitionSection> TMaterialTransitionSectionMap;

typedef struct TMeshContainer {

	TMaterialSectionMap MaterialSectionMap; // single materials map

	TMaterialTransitionSectionMap MaterialTransitionSectionMap; // materials with blending

} TMeshContainer;

typedef struct TMeshLodSection {

	FProcMeshSection WholeMesh; // whole mesh (collision only)

	TMeshContainer RegularMeshContainer; // used only for render main mesh

	TArray<TMeshContainer> TransitionPatchArray; // used for render transition 1 to 1 LOD patch mesh

	TArray<FVector> DebugPointList; // just point to draw debug. remove it after release

	TMeshLodSection() { 
		TransitionPatchArray.SetNum(6); 
	}

} TMeshLodSection;


typedef struct TMeshData {
	TArray<TMeshLodSection> MeshSectionLodArray;
	FProcMeshSection* CollisionMeshPtr;

	double TimeStamp = 0;
	uint32 VStamp = 0;
   
	unsigned short BaseMaterialId = 0;

	TMeshData() {
		MeshSectionLodArray.SetNum(LOD_ARRAY_SIZE); 
		CollisionMeshPtr = nullptr;
		md_counter++;
	}

	~TMeshData() {
		md_counter--;
	}

} TMeshData;

typedef std::shared_ptr<TMeshData> TMeshDataPtr;

typedef struct TVoxelDataParam {

	bool bGenerateLOD = false;

	int collisionLOD = 0;

	float ZCutLevel = 0;

	bool bZCut = false;

	bool bForceNoCache = false;

} TVoxelDataParam;
