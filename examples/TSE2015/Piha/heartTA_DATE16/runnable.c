#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "Generic/step.h"
#include "Cells/Generated/SinoatrialNode.h"
#include "Cells/Generated/BachmannBundle.h"
#include "Cells/Generated/LeftAtrium.h"
#include "Cells/Generated/LeftAtrium1.h"
#include "Cells/Generated/RightAtrium.h"
#include "Cells/Generated/RightAtrium1.h"
#include "Cells/Generated/CoronarySinus.h"
#include "Cells/Generated/CristaTerminalis.h"
#include "Cells/Generated/CristaTerminalis1.h"
#include "Cells/Generated/Ostium.h"
#include "Cells/Generated/Fast.h"
#include "Cells/Generated/Fast1.h"
#include "Cells/Generated/Slow.h"
#include "Cells/Generated/Slow1.h"
#include "Cells/Generated/AtrioventricularNode.h"
#include "Cells/Generated/BundleOfHis.h"
#include "Cells/Generated/BundleOfHis1.h"
#include "Cells/Generated/BundleOfHis2.h"
#include "Cells/Generated/LeftBundleBranch.h"
#include "Cells/Generated/LeftBundleBranch1.h"
#include "Cells/Generated/LeftVentricularApex.h"
#include "Cells/Generated/LeftVentricle.h"
#include "Cells/Generated/LeftVentricle1.h"
#include "Cells/Generated/LeftVentricularSeptum.h"
#include "Cells/Generated/LeftVentricularSeptum1.h"
#include "Cells/Generated/CSLeftVentricular.h"
#include "Cells/Generated/RightBundleBranch.h"
#include "Cells/Generated/RightBundleBranch1.h"
#include "Cells/Generated/RightVentricularApex.h"
#include "Cells/Generated/RightVentricle.h"
#include "Cells/Generated/RightVentricle1.h"
#include "Cells/Generated/RightVentricularSeptum.h"
#include "Cells/Generated/RightVentricularSeptum1.h"
#include "Paths/Generated/SA_BB.h"
#include "Paths/Generated/SA_OS.h"
#include "Paths/Generated/SA_RA.h"
#include "Paths/Generated/SA_CT.h"
#include "Paths/Generated/BB_LA.h"
#include "Paths/Generated/LA_LA1.h"
#include "Paths/Generated/RA_RA1.h"
#include "Paths/Generated/RA1_CS.h"
#include "Paths/Generated/CT_CT1.h"
#include "Paths/Generated/OS_Fast.h"
#include "Paths/Generated/Fast_Fast1.h"
#include "Paths/Generated/OS_Slow.h"
#include "Paths/Generated/Slow_Slow1.h"
#include "Paths/Generated/Fast1_AV.h"
#include "Paths/Generated/Slow1_AV.h"
#include "Paths/Generated/AV_His.h"
#include "Paths/Generated/His_His1.h"
#include "Paths/Generated/His1_His2.h"
#include "Paths/Generated/His2_LBB.h"
#include "Paths/Generated/LBB_LBB1.h"
#include "Paths/Generated/LBB1_LVA.h"
#include "Paths/Generated/His2_RBB.h"
#include "Paths/Generated/RBB_RBB1.h"
#include "Paths/Generated/RBB1_RVA.h"
#include "Paths/Generated/LVA_RVA.h"
#include "Paths/Generated/LVA_LV.h"
#include "Paths/Generated/LV_LV1.h"
#include "Paths/Generated/LVA_LVS.h"
#include "Paths/Generated/LVS_LVS1.h"
#include "Paths/Generated/LVS1_CSLV.h"
#include "Paths/Generated/RVA_RV.h"
#include "Paths/Generated/RV_RV1.h"
#include "Paths/Generated/RVA_RVS.h"
#include "Paths/Generated/RVS_RVS1.h"

SinoatrialNode SinoatrialNode_data;
BachmannBundle BachmannBundle_data;
LeftAtrium LeftAtrium_data;
LeftAtrium1 LeftAtrium1_data;
RightAtrium RightAtrium_data;
RightAtrium1 RightAtrium1_data;
CoronarySinus CoronarySinus_data;
CristaTerminalis CristaTerminalis_data;
CristaTerminalis1 CristaTerminalis1_data;
Ostium Ostium_data;
Fast Fast_data;
Fast1 Fast1_data;
Slow Slow_data;
Slow1 Slow1_data;
AtrioventricularNode AtrioventricularNode_data;
BundleOfHis BundleOfHis_data;
BundleOfHis1 BundleOfHis1_data;
BundleOfHis2 BundleOfHis2_data;
LeftBundleBranch LeftBundleBranch_data;
LeftBundleBranch1 LeftBundleBranch1_data;
LeftVentricularApex LeftVentricularApex_data;
LeftVentricle LeftVentricle_data;
LeftVentricle1 LeftVentricle1_data;
LeftVentricularSeptum LeftVentricularSeptum_data;
LeftVentricularSeptum1 LeftVentricularSeptum1_data;
CSLeftVentricular CSLeftVentricular_data;
RightBundleBranch RightBundleBranch_data;
RightBundleBranch1 RightBundleBranch1_data;
RightVentricularApex RightVentricularApex_data;
RightVentricle RightVentricle_data;
RightVentricle1 RightVentricle1_data;
RightVentricularSeptum RightVentricularSeptum_data;
RightVentricularSeptum1 RightVentricularSeptum1_data;
SA_BB SA_BB_data;
SA_OS SA_OS_data;
SA_RA SA_RA_data;
SA_CT SA_CT_data;
BB_LA BB_LA_data;
LA_LA1 LA_LA1_data;
RA_RA1 RA_RA1_data;
RA1_CS RA1_CS_data;
CT_CT1 CT_CT1_data;
OS_Fast OS_Fast_data;
Fast_Fast1 Fast_Fast1_data;
OS_Slow OS_Slow_data;
Slow_Slow1 Slow_Slow1_data;
Fast1_AV Fast1_AV_data;
Slow1_AV Slow1_AV_data;
AV_His AV_His_data;
His_His1 His_His1_data;
His1_His2 His1_His2_data;
His2_LBB His2_LBB_data;
LBB_LBB1 LBB_LBB1_data;
LBB1_LVA LBB1_LVA_data;
His2_RBB His2_RBB_data;
RBB_RBB1 RBB_RBB1_data;
RBB1_RVA RBB1_RVA_data;
LVA_RVA LVA_RVA_data;
LVA_LV LVA_LV_data;
LV_LV1 LV_LV1_data;
LVA_LVS LVA_LVS_data;
LVS_LVS1 LVS_LVS1_data;
LVS1_CSLV LVS1_CSLV_data;
RVA_RV RVA_RV_data;
RV_RV1 RV_RV1_data;
RVA_RVS RVA_RVS_data;
RVS_RVS1 RVS_RVS1_data;

int main(void) {
	(void) memset((void *)&SinoatrialNode_data, 0, sizeof(SinoatrialNode));
	SinoatrialNodeInit(&SinoatrialNode_data);

	(void) memset((void *)&BachmannBundle_data, 0, sizeof(BachmannBundle));
	BachmannBundleInit(&BachmannBundle_data);

	(void) memset((void *)&LeftAtrium_data, 0, sizeof(LeftAtrium));
	LeftAtriumInit(&LeftAtrium_data);

	(void) memset((void *)&LeftAtrium1_data, 0, sizeof(LeftAtrium1));
	LeftAtrium1Init(&LeftAtrium1_data);

	(void) memset((void *)&RightAtrium_data, 0, sizeof(RightAtrium));
	RightAtriumInit(&RightAtrium_data);

	(void) memset((void *)&RightAtrium1_data, 0, sizeof(RightAtrium1));
	RightAtrium1Init(&RightAtrium1_data);

	(void) memset((void *)&CoronarySinus_data, 0, sizeof(CoronarySinus));
	CoronarySinusInit(&CoronarySinus_data);

	(void) memset((void *)&CristaTerminalis_data, 0, sizeof(CristaTerminalis));
	CristaTerminalisInit(&CristaTerminalis_data);

	(void) memset((void *)&CristaTerminalis1_data, 0, sizeof(CristaTerminalis1));
	CristaTerminalis1Init(&CristaTerminalis1_data);

	(void) memset((void *)&Ostium_data, 0, sizeof(Ostium));
	OstiumInit(&Ostium_data);

	(void) memset((void *)&Fast_data, 0, sizeof(Fast));
	FastInit(&Fast_data);

	(void) memset((void *)&Fast1_data, 0, sizeof(Fast1));
	Fast1Init(&Fast1_data);

	(void) memset((void *)&Slow_data, 0, sizeof(Slow));
	SlowInit(&Slow_data);

	(void) memset((void *)&Slow1_data, 0, sizeof(Slow1));
	Slow1Init(&Slow1_data);

	(void) memset((void *)&AtrioventricularNode_data, 0, sizeof(AtrioventricularNode));
	AtrioventricularNodeInit(&AtrioventricularNode_data);

	(void) memset((void *)&BundleOfHis_data, 0, sizeof(BundleOfHis));
	BundleOfHisInit(&BundleOfHis_data);

	(void) memset((void *)&BundleOfHis1_data, 0, sizeof(BundleOfHis1));
	BundleOfHis1Init(&BundleOfHis1_data);

	(void) memset((void *)&BundleOfHis2_data, 0, sizeof(BundleOfHis2));
	BundleOfHis2Init(&BundleOfHis2_data);

	(void) memset((void *)&LeftBundleBranch_data, 0, sizeof(LeftBundleBranch));
	LeftBundleBranchInit(&LeftBundleBranch_data);

	(void) memset((void *)&LeftBundleBranch1_data, 0, sizeof(LeftBundleBranch1));
	LeftBundleBranch1Init(&LeftBundleBranch1_data);

	(void) memset((void *)&LeftVentricularApex_data, 0, sizeof(LeftVentricularApex));
	LeftVentricularApexInit(&LeftVentricularApex_data);

	(void) memset((void *)&LeftVentricle_data, 0, sizeof(LeftVentricle));
	LeftVentricleInit(&LeftVentricle_data);

	(void) memset((void *)&LeftVentricle1_data, 0, sizeof(LeftVentricle1));
	LeftVentricle1Init(&LeftVentricle1_data);

	(void) memset((void *)&LeftVentricularSeptum_data, 0, sizeof(LeftVentricularSeptum));
	LeftVentricularSeptumInit(&LeftVentricularSeptum_data);

	(void) memset((void *)&LeftVentricularSeptum1_data, 0, sizeof(LeftVentricularSeptum1));
	LeftVentricularSeptum1Init(&LeftVentricularSeptum1_data);

	(void) memset((void *)&CSLeftVentricular_data, 0, sizeof(CSLeftVentricular));
	CSLeftVentricularInit(&CSLeftVentricular_data);

	(void) memset((void *)&RightBundleBranch_data, 0, sizeof(RightBundleBranch));
	RightBundleBranchInit(&RightBundleBranch_data);

	(void) memset((void *)&RightBundleBranch1_data, 0, sizeof(RightBundleBranch1));
	RightBundleBranch1Init(&RightBundleBranch1_data);

	(void) memset((void *)&RightVentricularApex_data, 0, sizeof(RightVentricularApex));
	RightVentricularApexInit(&RightVentricularApex_data);

	(void) memset((void *)&RightVentricle_data, 0, sizeof(RightVentricle));
	RightVentricleInit(&RightVentricle_data);

	(void) memset((void *)&RightVentricle1_data, 0, sizeof(RightVentricle1));
	RightVentricle1Init(&RightVentricle1_data);

	(void) memset((void *)&RightVentricularSeptum_data, 0, sizeof(RightVentricularSeptum));
	RightVentricularSeptumInit(&RightVentricularSeptum_data);

	(void) memset((void *)&RightVentricularSeptum1_data, 0, sizeof(RightVentricularSeptum1));
	RightVentricularSeptum1Init(&RightVentricularSeptum1_data);

	(void) memset((void *)&SA_BB_data, 0, sizeof(SA_BB));
	SA_BBInit(&SA_BB_data);

	(void) memset((void *)&SA_OS_data, 0, sizeof(SA_OS));
	SA_OSInit(&SA_OS_data);

	(void) memset((void *)&SA_RA_data, 0, sizeof(SA_RA));
	SA_RAInit(&SA_RA_data);

	(void) memset((void *)&SA_CT_data, 0, sizeof(SA_CT));
	SA_CTInit(&SA_CT_data);

	(void) memset((void *)&BB_LA_data, 0, sizeof(BB_LA));
	BB_LAInit(&BB_LA_data);

	(void) memset((void *)&LA_LA1_data, 0, sizeof(LA_LA1));
	LA_LA1Init(&LA_LA1_data);

	(void) memset((void *)&RA_RA1_data, 0, sizeof(RA_RA1));
	RA_RA1Init(&RA_RA1_data);

	(void) memset((void *)&RA1_CS_data, 0, sizeof(RA1_CS));
	RA1_CSInit(&RA1_CS_data);

	(void) memset((void *)&CT_CT1_data, 0, sizeof(CT_CT1));
	CT_CT1Init(&CT_CT1_data);

	(void) memset((void *)&OS_Fast_data, 0, sizeof(OS_Fast));
	OS_FastInit(&OS_Fast_data);

	(void) memset((void *)&Fast_Fast1_data, 0, sizeof(Fast_Fast1));
	Fast_Fast1Init(&Fast_Fast1_data);

	(void) memset((void *)&OS_Slow_data, 0, sizeof(OS_Slow));
	OS_SlowInit(&OS_Slow_data);

	(void) memset((void *)&Slow_Slow1_data, 0, sizeof(Slow_Slow1));
	Slow_Slow1Init(&Slow_Slow1_data);

	(void) memset((void *)&Fast1_AV_data, 0, sizeof(Fast1_AV));
	Fast1_AVInit(&Fast1_AV_data);

	(void) memset((void *)&Slow1_AV_data, 0, sizeof(Slow1_AV));
	Slow1_AVInit(&Slow1_AV_data);

	(void) memset((void *)&AV_His_data, 0, sizeof(AV_His));
	AV_HisInit(&AV_His_data);

	(void) memset((void *)&His_His1_data, 0, sizeof(His_His1));
	His_His1Init(&His_His1_data);

	(void) memset((void *)&His1_His2_data, 0, sizeof(His1_His2));
	His1_His2Init(&His1_His2_data);

	(void) memset((void *)&His2_LBB_data, 0, sizeof(His2_LBB));
	His2_LBBInit(&His2_LBB_data);

	(void) memset((void *)&LBB_LBB1_data, 0, sizeof(LBB_LBB1));
	LBB_LBB1Init(&LBB_LBB1_data);

	(void) memset((void *)&LBB1_LVA_data, 0, sizeof(LBB1_LVA));
	LBB1_LVAInit(&LBB1_LVA_data);

	(void) memset((void *)&His2_RBB_data, 0, sizeof(His2_RBB));
	His2_RBBInit(&His2_RBB_data);

	(void) memset((void *)&RBB_RBB1_data, 0, sizeof(RBB_RBB1));
	RBB_RBB1Init(&RBB_RBB1_data);

	(void) memset((void *)&RBB1_RVA_data, 0, sizeof(RBB1_RVA));
	RBB1_RVAInit(&RBB1_RVA_data);

	(void) memset((void *)&LVA_RVA_data, 0, sizeof(LVA_RVA));
	LVA_RVAInit(&LVA_RVA_data);

	(void) memset((void *)&LVA_LV_data, 0, sizeof(LVA_LV));
	LVA_LVInit(&LVA_LV_data);

	(void) memset((void *)&LV_LV1_data, 0, sizeof(LV_LV1));
	LV_LV1Init(&LV_LV1_data);

	(void) memset((void *)&LVA_LVS_data, 0, sizeof(LVA_LVS));
	LVA_LVSInit(&LVA_LVS_data);

	(void) memset((void *)&LVS_LVS1_data, 0, sizeof(LVS_LVS1));
	LVS_LVS1Init(&LVS_LVS1_data);

	(void) memset((void *)&LVS1_CSLV_data, 0, sizeof(LVS1_CSLV));
	LVS1_CSLVInit(&LVS1_CSLV_data);

	(void) memset((void *)&RVA_RV_data, 0, sizeof(RVA_RV));
	RVA_RVInit(&RVA_RV_data);

	(void) memset((void *)&RV_RV1_data, 0, sizeof(RV_RV1));
	RV_RV1Init(&RV_RV1_data);

	(void) memset((void *)&RVA_RVS_data, 0, sizeof(RVA_RVS));
	RVA_RVSInit(&RVA_RVS_data);

	(void) memset((void *)&RVS_RVS1_data, 0, sizeof(RVS_RVS1));
	RVS_RVS1Init(&RVS_RVS1_data);

	//FILE* fo = fopen("out.csv", "w");

	asm("#@PRET_Parse start");
	asm("#@PRET_Thread start PRET_Node_main_ID_0");

	unsigned int i = 0;
	for(i=0; i < (SIMULATION_TIME / STEP_SIZE); i++) {
		asm("#@PRET_EOT start");
		asm("#@PRET_EOT end");


//fprintf(fo, "%u, %u\n", i*STEP_SIZE, SinoatrialNode_data.t);
//fflush(fo);

/* Cell Mappings */

// SA Node


// Left Atrium
BachmannBundle_data.ACTcell = SA_BB_data.ACTcell;

LeftAtrium_data.ACTcell = BB_LA_data.ACTcell;

LeftAtrium1_data.ACTcell = LA_LA1_data.ACTcell;


// Right Atrium
RightAtrium_data.ACTcell = SA_RA_data.ACTcell;

RightAtrium1_data.ACTcell = RA_RA1_data.ACTcell;

CoronarySinus_data.ACTcell = RA1_CS_data.ACTcell;


// Crista Terminalis
CristaTerminalis_data.ACTcell = SA_CT_data.ACTcell;

CristaTerminalis1_data.ACTcell = CT_CT1_data.ACTcell;


// AV Loop
Ostium_data.ACTcell = SA_OS_data.ACTcell;

Fast_data.ACTcell = OS_Fast_data.ACTcell;

Fast1_data.ACTcell = Fast_Fast1_data.ACTcell;

Slow_data.ACTcell = OS_Slow_data.ACTcell;

Slow1_data.ACTcell = Slow_Slow1_data.ACTcell;

AtrioventricularNode_data.ACTcell1 = Slow1_AV_data.ACTcell;
AtrioventricularNode_data.ACTcell2 = Fast1_AV_data.ACTcell;


// Bundle of His
BundleOfHis_data.ACTcell = AV_His_data.ACTcell;

BundleOfHis1_data.ACTcell = His_His1_data.ACTcell;

BundleOfHis2_data.ACTcell = His1_His2_data.ACTcell;


// Bundle Branch Loop
LeftBundleBranch_data.ACTcell = His2_LBB_data.ACTcell;

LeftBundleBranch1_data.ACTcell = LBB_LBB1_data.ACTcell;

LeftVentricularApex_data.ACTcell = LBB1_LVA_data.ACTcell;

RightBundleBranch_data.ACTcell = His2_RBB_data.ACTcell;

RightBundleBranch1_data.ACTcell = RBB_RBB1_data.ACTcell;

RightVentricularApex_data.ACTcell = RBB1_RVA_data.ACTcell;


// Left Ventricle
LeftVentricle_data.ACTcell = LVA_LV_data.ACTcell;

LeftVentricle1_data.ACTcell = LV_LV1_data.ACTcell;


// Left Ventricular Septum
LeftVentricularSeptum_data.ACTcell = LVA_LVS_data.ACTcell;

LeftVentricularSeptum1_data.ACTcell = LVS_LVS1_data.ACTcell;

CSLeftVentricular_data.ACTcell = LVS1_CSLV_data.ACTcell;


// Right Ventricle
RightVentricle_data.ACTcell = RVA_RV_data.ACTcell;

RightVentricle1_data.ACTcell = RV_RV1_data.ACTcell;


// Right Ventricular Septum
RightVentricularSeptum_data.ACTcell = RVA_RVS_data.ACTcell;

RightVentricularSeptum1_data.ACTcell = RVS_RVS1_data.ACTcell;



/* Path Mappings */

// SA
SA_BB_data.ACTpath = SinoatrialNode_data.ACTpath;

SA_OS_data.ACTpath = SinoatrialNode_data.ACTpath;

SA_RA_data.ACTpath = SinoatrialNode_data.ACTpath;

SA_CT_data.ACTpath = SinoatrialNode_data.ACTpath;


// Left Atrium Branch
BB_LA_data.ACTpath = BachmannBundle_data.ACTpath;

LA_LA1_data.ACTpath = LeftAtrium_data.ACTpath;


// Right Atrium Branch
RA_RA1_data.ACTpath = RightAtrium_data.ACTpath;

RA1_CS_data.ACTpath = RightAtrium1_data.ACTpath;


// CT Branch
CT_CT1_data.ACTpath = CristaTerminalis_data.ACTpath;


// AV Loop
OS_Fast_data.ACTpath = Ostium_data.ACTpath;

OS_Slow_data.ACTpath = Ostium_data.ACTpath;

Fast_Fast1_data.ACTpath = Fast_data.ACTpath;

Fast1_AV_data.ACTpath = Fast1_data.ACTpath;

Slow_Slow1_data.ACTpath = Slow_data.ACTpath;

Slow1_AV_data.ACTpath = Slow1_data.ACTpath;


// His Bundle
AV_His_data.ACTpath = AtrioventricularNode_data.ACTpath;

His_His1_data.ACTpath = BundleOfHis_data.ACTpath;

His1_His2_data.ACTpath = BundleOfHis1_data.ACTpath;


// Bundle Branch Loop
His2_LBB_data.ACTpath = BundleOfHis2_data.ACTpath;

LBB_LBB1_data.ACTpath = LeftBundleBranch_data.ACTpath;

LBB1_LVA_data.ACTpath = LeftBundleBranch1_data.ACTpath;

His2_RBB_data.ACTpath = BundleOfHis2_data.ACTpath;

RBB_RBB1_data.ACTpath = RightBundleBranch_data.ACTpath;

RBB1_RVA_data.ACTpath = RightBundleBranch1_data.ACTpath;


// Left Ventricle
LVA_LV_data.ACTpath = LeftVentricularApex_data.ACTpath;

LV_LV1_data.ACTpath = LeftVentricle_data.ACTpath;

LVA_LVS_data.ACTpath = LeftVentricularApex_data.ACTpath;

LVS_LVS1_data.ACTpath = LeftVentricularSeptum_data.ACTpath;

LVS1_CSLV_data.ACTpath = LeftVentricularSeptum1_data.ACTpath;


// Right Ventricle
RVA_RV_data.ACTpath = RightVentricularApex_data.ACTpath;

RV_RV1_data.ACTpath = RightVentricle_data.ACTpath;

RVA_RVS_data.ACTpath = RightVentricularApex_data.ACTpath;

RVS_RVS1_data.ACTpath = RightVentricularSeptum_data.ACTpath;

		SinoatrialNodeRun(&SinoatrialNode_data);

		BachmannBundleRun(&BachmannBundle_data);

		LeftAtriumRun(&LeftAtrium_data);

		LeftAtrium1Run(&LeftAtrium1_data);

		RightAtriumRun(&RightAtrium_data);

		RightAtrium1Run(&RightAtrium1_data);

		CoronarySinusRun(&CoronarySinus_data);

		CristaTerminalisRun(&CristaTerminalis_data);

		CristaTerminalis1Run(&CristaTerminalis1_data);

		OstiumRun(&Ostium_data);

		FastRun(&Fast_data);

		Fast1Run(&Fast1_data);

		SlowRun(&Slow_data);

		Slow1Run(&Slow1_data);

		AtrioventricularNodeRun(&AtrioventricularNode_data);

		BundleOfHisRun(&BundleOfHis_data);

		BundleOfHis1Run(&BundleOfHis1_data);

		BundleOfHis2Run(&BundleOfHis2_data);

		LeftBundleBranchRun(&LeftBundleBranch_data);

		LeftBundleBranch1Run(&LeftBundleBranch1_data);

		LeftVentricularApexRun(&LeftVentricularApex_data);

		LeftVentricleRun(&LeftVentricle_data);

		LeftVentricle1Run(&LeftVentricle1_data);

		LeftVentricularSeptumRun(&LeftVentricularSeptum_data);

		LeftVentricularSeptum1Run(&LeftVentricularSeptum1_data);

		CSLeftVentricularRun(&CSLeftVentricular_data);

		RightBundleBranchRun(&RightBundleBranch_data);

		RightBundleBranch1Run(&RightBundleBranch1_data);

		RightVentricularApexRun(&RightVentricularApex_data);

		RightVentricleRun(&RightVentricle_data);

		RightVentricle1Run(&RightVentricle1_data);

		RightVentricularSeptumRun(&RightVentricularSeptum_data);

		RightVentricularSeptum1Run(&RightVentricularSeptum1_data);

		SA_BBRun(&SA_BB_data);

		SA_OSRun(&SA_OS_data);

		SA_RARun(&SA_RA_data);

		SA_CTRun(&SA_CT_data);

		BB_LARun(&BB_LA_data);

		LA_LA1Run(&LA_LA1_data);

		RA_RA1Run(&RA_RA1_data);

		RA1_CSRun(&RA1_CS_data);

		CT_CT1Run(&CT_CT1_data);

		OS_FastRun(&OS_Fast_data);

		Fast_Fast1Run(&Fast_Fast1_data);

		OS_SlowRun(&OS_Slow_data);

		Slow_Slow1Run(&Slow_Slow1_data);

		Fast1_AVRun(&Fast1_AV_data);

		Slow1_AVRun(&Slow1_AV_data);

		AV_HisRun(&AV_His_data);

		His_His1Run(&His_His1_data);

		His1_His2Run(&His1_His2_data);

		His2_LBBRun(&His2_LBB_data);

		LBB_LBB1Run(&LBB_LBB1_data);

		LBB1_LVARun(&LBB1_LVA_data);

		His2_RBBRun(&His2_RBB_data);

		RBB_RBB1Run(&RBB_RBB1_data);

		RBB1_RVARun(&RBB1_RVA_data);

		LVA_RVARun(&LVA_RVA_data);

		LVA_LVRun(&LVA_LV_data);

		LV_LV1Run(&LV_LV1_data);

		LVA_LVSRun(&LVA_LVS_data);

		LVS_LVS1Run(&LVS_LVS1_data);

		LVS1_CSLVRun(&LVS1_CSLV_data);

		RVA_RVRun(&RVA_RV_data);

		RV_RV1Run(&RV_RV1_data);

		RVA_RVSRun(&RVA_RVS_data);

		RVS_RVS1Run(&RVS_RVS1_data);
	}

	//fclose(fo);

	return 0;
}
