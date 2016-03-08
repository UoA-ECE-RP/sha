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