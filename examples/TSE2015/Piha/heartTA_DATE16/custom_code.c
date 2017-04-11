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