#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64
#include <Windows.h>

	
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;
	
	GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

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

	FILE* fo = fopen("out.csv", "w");

	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	unsigned int i = 0;
	for(i=0; i < (SIMULATION_TIME / STEP_SIZE); i++) {
		//fprintf(stdout, "Time: %fms\n", i*STEP_SIZE);
		//fflush(stdout);

//fprintf(fo, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", i*STEP_SIZE, SinoatrialNode_data.v, Ostium_data.v, Fast_data.v, Fast1_data.v, AtrioventricularNode_data.v, BundleOfHis_data.v, BundleOfHis1_data.v, BundleOfHis2_data.v, RightBundleBranch_data.v, RightBundleBranch1_data.v, RightVentricularApex_data.v);
//fflush(fo);

double stim_voltage = 0;

unsigned long cycle_step = i % (unsigned long) (500 / STEP_SIZE);
if(cycle_step >= (10 / STEP_SIZE) && cycle_step < (15 / STEP_SIZE)) {
	stim_voltage = 262;
}

/* Cell Mappings */

// SA Node
SinoatrialNode_data.v_i_0 = stim_voltage;
SinoatrialNode_data.v_i_1 = SA_BB_data.cell2_v_replay;
SinoatrialNode_data.v_i_2 = SA_OS_data.cell2_v_replay;
SinoatrialNode_data.v_i_3 = SA_RA_data.cell2_v_replay;
SinoatrialNode_data.v_i_4 = SA_CT_data.cell2_v_replay;


// Left Atrium
BachmannBundle_data.v_i_0 = SA_BB_data.cell1_v_replay;
BachmannBundle_data.v_i_1 = BB_LA_data.cell2_v_replay;

LeftAtrium_data.v_i_0 = BB_LA_data.cell1_v_replay;
LeftAtrium_data.v_i_1 = LA_LA1_data.cell2_v_replay;

LeftAtrium1_data.v_i_0 = LA_LA1_data.cell1_v_replay;


// Right Atrium
RightAtrium_data.v_i_0 = SA_RA_data.cell1_v_replay;
RightAtrium_data.v_i_1 = RA_RA1_data.cell2_v_replay;

RightAtrium1_data.v_i_0 = RA_RA1_data.cell1_v_replay;
RightAtrium1_data.v_i_1 = RA1_CS_data.cell2_v_replay;

CoronarySinus_data.v_i_0 = RA1_CS_data.cell1_v_replay;


// Crista Terminalis
CristaTerminalis_data.v_i_0 = SA_CT_data.cell1_v_replay;
CristaTerminalis_data.v_i_1 = CT_CT1_data.cell2_v_replay;

CristaTerminalis1_data.v_i_0 = CT_CT1_data.cell1_v_replay;


// AV Loop
Ostium_data.v_i_0 = SA_OS_data.cell1_v_replay;
Ostium_data.v_i_1 = OS_Slow_data.cell2_v_replay;
Ostium_data.v_i_2 = OS_Fast_data.cell2_v_replay;

Fast_data.v_i_0 = OS_Fast_data.cell1_v_replay;
Fast_data.v_i_1 = Fast_Fast1_data.cell2_v_replay;

Fast1_data.v_i_0 = Fast_Fast1_data.cell1_v_replay;
Fast1_data.v_i_1 = Fast1_AV_data.cell2_v_replay;

Slow_data.v_i_0 = OS_Slow_data.cell1_v_replay;
Slow_data.v_i_1 = Slow_Slow1_data.cell2_v_replay;

Slow1_data.v_i_0 = Slow_Slow1_data.cell1_v_replay;
Slow1_data.v_i_1 = Slow1_AV_data.cell2_v_replay;

AtrioventricularNode_data.v_i_0 = Slow1_AV_data.cell1_v_replay;
AtrioventricularNode_data.v_i_1 = Fast1_AV_data.cell1_v_replay;
AtrioventricularNode_data.v_i_2 = AV_His_data.cell2_v_replay;


// Bundle of His
BundleOfHis_data.v_i_0 = AV_His_data.cell1_v_replay;
BundleOfHis_data.v_i_1 = His_His1_data.cell2_v_replay;

BundleOfHis1_data.v_i_0 = His_His1_data.cell1_v_replay;
BundleOfHis1_data.v_i_1 = His1_His2_data.cell2_v_replay;

BundleOfHis2_data.v_i_0 = His1_His2_data.cell1_v_replay;
BundleOfHis2_data.v_i_1 = His2_LBB_data.cell2_v_replay;
BundleOfHis2_data.v_i_2 = His2_RBB_data.cell2_v_replay;


// Bundle Branch Loop
LeftBundleBranch_data.v_i_0 = His2_LBB_data.cell1_v_replay;
LeftBundleBranch_data.v_i_1 = LBB_LBB1_data.cell2_v_replay;

LeftBundleBranch1_data.v_i_0 = LBB_LBB1_data.cell1_v_replay;
LeftBundleBranch1_data.v_i_1 = LBB1_LVA_data.cell2_v_replay;

LeftVentricularApex_data.v_i_0 = LVA_RVA_data.cell2_v_replay;
LeftVentricularApex_data.v_i_1 = LBB1_LVA_data.cell1_v_replay;
LeftVentricularApex_data.v_i_2 = LVA_LV_data.cell2_v_replay;
LeftVentricularApex_data.v_i_3 = LVA_LVS_data.cell2_v_replay;

RightBundleBranch_data.v_i_0 = His2_RBB_data.cell1_v_replay;
RightBundleBranch_data.v_i_1 = RBB_RBB1_data.cell2_v_replay;

RightBundleBranch1_data.v_i_0 = RBB_RBB1_data.cell1_v_replay;
RightBundleBranch1_data.v_i_1 = RBB1_RVA_data.cell2_v_replay;

RightVentricularApex_data.v_i_0 = RBB1_RVA_data.cell1_v_replay;
RightVentricularApex_data.v_i_1 = RVA_RV_data.cell2_v_replay;
RightVentricularApex_data.v_i_2 = RVA_RVS_data.cell2_v_replay;
RightVentricularApex_data.v_i_3 = LVA_RVA_data.cell1_v_replay;


// Left Ventricle
LeftVentricle_data.v_i_0 = LVA_LV_data.cell1_v_replay;
LeftVentricle_data.v_i_1 = LV_LV1_data.cell2_v_replay;

LeftVentricle1_data.v_i_0 = LV_LV1_data.cell1_v_replay;


// Left Ventricular Septum
LeftVentricularSeptum_data.v_i_0 = LVA_LVS_data.cell1_v_replay;
LeftVentricularSeptum_data.v_i_1 = LVS_LVS1_data.cell2_v_replay;

LeftVentricularSeptum1_data.v_i_0 = LVS_LVS1_data.cell1_v_replay;
LeftVentricularSeptum1_data.v_i_1 = LVS1_CSLV_data.cell2_v_replay;

CSLeftVentricular_data.v_i_0 = LVS1_CSLV_data.cell1_v_replay;


// Right Ventricle
RightVentricle_data.v_i_0 = RVA_RV_data.cell1_v_replay;
RightVentricle_data.v_i_1 = RV_RV1_data.cell2_v_replay;

RightVentricle1_data.v_i_0 = RV_RV1_data.cell1_v_replay;


// Right Ventricular Septum
RightVentricularSeptum_data.v_i_0 = RVA_RVS_data.cell1_v_replay;
RightVentricularSeptum_data.v_i_1 = RVS_RVS1_data.cell2_v_replay;

RightVentricularSeptum1_data.v_i_0 = RVS_RVS1_data.cell1_v_replay;



/* Path Mappings */

// SA
SA_BB_data.cell1_v = SinoatrialNode_data.v;
SA_BB_data.cell1_mode = SinoatrialNode_data.state;
SA_BB_data.cell2_v = BachmannBundle_data.v;
SA_BB_data.cell2_mode = BachmannBundle_data.state;

SA_OS_data.cell1_v = SinoatrialNode_data.v;
SA_OS_data.cell1_mode = SinoatrialNode_data.state;
SA_OS_data.cell2_v = Ostium_data.v;
SA_OS_data.cell2_mode = Ostium_data.state;

SA_RA_data.cell1_v = SinoatrialNode_data.v;
SA_RA_data.cell1_mode = SinoatrialNode_data.state;
SA_RA_data.cell2_v = RightAtrium_data.v;
SA_RA_data.cell2_mode = RightAtrium_data.state;

SA_CT_data.cell1_v = SinoatrialNode_data.v;
SA_CT_data.cell1_mode = SinoatrialNode_data.state;
SA_CT_data.cell2_v = CristaTerminalis_data.v;
SA_CT_data.cell2_mode = CristaTerminalis_data.state;

SA_BB_data.cell1_v = SinoatrialNode_data.v;
SA_BB_data.cell1_mode = SinoatrialNode_data.state;
SA_BB_data.cell2_v = BachmannBundle_data.v;
SA_BB_data.cell2_mode = BachmannBundle_data.state;


// Left Atrium Branch
BB_LA_data.cell1_v = BachmannBundle_data.v;
BB_LA_data.cell1_mode = BachmannBundle_data.state;
BB_LA_data.cell2_v = LeftAtrium_data.v;
BB_LA_data.cell2_mode = LeftAtrium_data.state;

LA_LA1_data.cell1_v = LeftAtrium_data.v;
LA_LA1_data.cell1_mode = LeftAtrium_data.state;
LA_LA1_data.cell2_v = LeftAtrium1_data.v;
LA_LA1_data.cell2_mode = LeftAtrium1_data.state;


// Right Atrium Branch
RA_RA1_data.cell1_v = RightAtrium_data.v;
RA_RA1_data.cell1_mode = RightAtrium_data.state;
RA_RA1_data.cell2_v = RightAtrium1_data.v;
RA_RA1_data.cell2_mode = RightAtrium1_data.state;

RA1_CS_data.cell1_v = RightAtrium1_data.v;
RA1_CS_data.cell1_mode = RightAtrium1_data.state;
RA1_CS_data.cell2_v = CoronarySinus_data.v;
RA1_CS_data.cell2_mode = CoronarySinus_data.state;


// CT Branch
CT_CT1_data.cell1_v = CristaTerminalis_data.v;
CT_CT1_data.cell1_mode = CristaTerminalis_data.state;
CT_CT1_data.cell2_v = CristaTerminalis1_data.v;
CT_CT1_data.cell2_mode = CristaTerminalis1_data.state;


// AV Loop
OS_Fast_data.cell1_v = Ostium_data.v;
OS_Fast_data.cell1_mode = Ostium_data.state;
OS_Fast_data.cell2_v = Fast_data.v;
OS_Fast_data.cell2_mode = Fast_data.state;

OS_Slow_data.cell1_v = Ostium_data.v;
OS_Slow_data.cell1_mode = Ostium_data.state;
OS_Slow_data.cell2_v = Slow_data.v;
OS_Slow_data.cell2_mode = Slow_data.state;

Fast_Fast1_data.cell1_v = Fast_data.v;
Fast_Fast1_data.cell1_mode = Fast_data.state;
Fast_Fast1_data.cell2_v = Fast1_data.v;
Fast_Fast1_data.cell2_mode = Fast1_data.state;

Fast1_AV_data.cell1_v = Fast1_data.v;
Fast1_AV_data.cell1_mode = Fast1_data.state;
Fast1_AV_data.cell2_v = AtrioventricularNode_data.v;
Fast1_AV_data.cell2_mode = AtrioventricularNode_data.state;

Slow_Slow1_data.cell1_v = Slow_data.v;
Slow_Slow1_data.cell1_mode = Slow_data.state;
Slow_Slow1_data.cell2_v = Slow1_data.v;
Slow_Slow1_data.cell2_mode = Slow1_data.state;

Slow1_AV_data.cell1_v = Slow1_data.v;
Slow1_AV_data.cell1_mode = Slow1_data.state;
Slow1_AV_data.cell2_v = AtrioventricularNode_data.v;
Slow1_AV_data.cell2_mode = AtrioventricularNode_data.state;


// His Bundle
AV_His_data.cell1_v = AtrioventricularNode_data.v;
AV_His_data.cell1_mode = AtrioventricularNode_data.state;
AV_His_data.cell2_v = BundleOfHis_data.v;
AV_His_data.cell2_mode = BundleOfHis_data.state;

His_His1_data.cell1_v = BundleOfHis_data.v;
His_His1_data.cell1_mode = BundleOfHis_data.state;
His_His1_data.cell2_v = BundleOfHis1_data.v;
His_His1_data.cell2_mode = BundleOfHis1_data.state;

His1_His2_data.cell1_v = BundleOfHis1_data.v;
His1_His2_data.cell1_mode = BundleOfHis1_data.state;
His1_His2_data.cell2_v = BundleOfHis2_data.v;
His1_His2_data.cell2_mode = BundleOfHis2_data.state;


// Bundle Branch Loop
His2_LBB_data.cell1_v = BundleOfHis2_data.v;
His2_LBB_data.cell1_mode = BundleOfHis2_data.state;
His2_LBB_data.cell2_v = LeftBundleBranch_data.v;
His2_LBB_data.cell2_mode = LeftBundleBranch_data.state;

LBB_LBB1_data.cell1_v = LeftBundleBranch_data.v;
LBB_LBB1_data.cell1_mode = LeftBundleBranch_data.state;
LBB_LBB1_data.cell2_v = LeftBundleBranch1_data.v;
LBB_LBB1_data.cell2_mode = LeftBundleBranch1_data.state;

LBB1_LVA_data.cell1_v = LeftBundleBranch1_data.v;
LBB1_LVA_data.cell1_mode = LeftBundleBranch1_data.state;
LBB1_LVA_data.cell2_v = LeftVentricularApex_data.v;
LBB1_LVA_data.cell2_mode = LeftVentricularApex_data.state;

His2_RBB_data.cell1_v = BundleOfHis2_data.v;
His2_RBB_data.cell1_mode = BundleOfHis2_data.state;
His2_RBB_data.cell2_v = RightBundleBranch_data.v;
His2_RBB_data.cell2_mode = RightBundleBranch_data.state;

RBB_RBB1_data.cell1_v = RightBundleBranch_data.v;
RBB_RBB1_data.cell1_mode = RightBundleBranch_data.state;
RBB_RBB1_data.cell2_v = RightBundleBranch1_data.v;
RBB_RBB1_data.cell2_mode = RightBundleBranch1_data.state;

RBB1_RVA_data.cell1_v = RightBundleBranch1_data.v;
RBB1_RVA_data.cell1_mode = RightBundleBranch1_data.state;
RBB1_RVA_data.cell2_v = RightVentricularApex_data.v;
RBB1_RVA_data.cell2_mode = RightVentricularApex_data.state;

LVA_RVA_data.cell1_v = LeftVentricularApex_data.v;
LVA_RVA_data.cell1_mode = LeftVentricularApex_data.state;
LVA_RVA_data.cell2_v = RightVentricularApex_data.v;
LVA_RVA_data.cell2_mode = RightVentricularApex_data.state;


// Left Ventricle
LVA_LV_data.cell1_v = LeftVentricularApex_data.v;
LVA_LV_data.cell1_mode = LeftVentricularApex_data.state;
LVA_LV_data.cell2_v = LeftVentricle_data.v;
LVA_LV_data.cell2_mode = LeftVentricle_data.state;

LV_LV1_data.cell1_v = LeftVentricle_data.v;
LV_LV1_data.cell1_mode = LeftVentricle_data.state;
LV_LV1_data.cell2_v = LeftVentricle1_data.v;
LV_LV1_data.cell2_mode = LeftVentricle1_data.state;

LVA_LVS_data.cell1_v = LeftVentricularApex_data.v;
LVA_LVS_data.cell1_mode = LeftVentricularApex_data.state;
LVA_LVS_data.cell2_v = LeftVentricularSeptum_data.v;
LVA_LVS_data.cell2_mode = LeftVentricularSeptum_data.state;

LVS_LVS1_data.cell1_v = LeftVentricularSeptum_data.v;
LVS_LVS1_data.cell1_mode = LeftVentricularSeptum_data.state;
LVS_LVS1_data.cell2_v = LeftVentricularSeptum1_data.v;
LVS_LVS1_data.cell2_mode = LeftVentricularSeptum1_data.state;

LVS1_CSLV_data.cell1_v = LeftVentricularSeptum1_data.v;
LVS1_CSLV_data.cell1_mode = LeftVentricularSeptum1_data.state;
LVS1_CSLV_data.cell2_v = CSLeftVentricular_data.v;
LVS1_CSLV_data.cell2_mode = CSLeftVentricular_data.state;


// Right Ventricle
RVA_RV_data.cell1_v = RightVentricularApex_data.v;
RVA_RV_data.cell1_mode = RightVentricularApex_data.state;
RVA_RV_data.cell2_v = RightVentricle_data.v;
RVA_RV_data.cell2_mode = RightVentricle_data.state;

RV_RV1_data.cell1_v = RightVentricle_data.v;
RV_RV1_data.cell1_mode = RightVentricle_data.state;
RV_RV1_data.cell2_v = RightVentricle1_data.v;
RV_RV1_data.cell2_mode = RightVentricle1_data.state;

RVA_RVS_data.cell1_v = RightVentricularApex_data.v;
RVA_RVS_data.cell1_mode = RightVentricularApex_data.state;
RVA_RVS_data.cell2_v = RightVentricularSeptum_data.v;
RVA_RVS_data.cell2_mode = RightVentricularSeptum_data.state;

RVS_RVS1_data.cell1_v = RightVentricularSeptum_data.v;
RVS_RVS1_data.cell1_mode = RightVentricularSeptum_data.state;
RVS_RVS1_data.cell2_v = RightVentricularSeptum1_data.v;
RVS_RVS1_data.cell2_mode = RightVentricularSeptum1_data.state;

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

	gettimeofday(&t1, 0);
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;

	printf("Time taken: %ld microseconds (%.3f seconds)\n", elapsed, (elapsed / 1000000.0));

	fclose(fo);

	return 0;
}
