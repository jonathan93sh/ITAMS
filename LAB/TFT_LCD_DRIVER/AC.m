F_CPU = 48*10^6;

T_CPU = F_CPU^-1;

ns = 10^-9;

tcs = 15*ns;
twcl = 30*ns;
trcs = 45*ns;
twch =0
twc  =0

tdst =0
trcsfm = 355*ns
trdhfm = 90*ns

tcsf = 5*ns;

%% calc nops

tcs_NOP = ceil(tcs/T_CPU)

trcsfm_NOP = ceil(trcsfm/T_CPU)

trdhfm_NOP = ceil(trdhfm/T_CPU)

tcsf_NOP = ceil(tcsf/T_CPU)

twcl_NOP = ceil(twcl/T_CPU)

trcs_NOP = ceil(trcs/T_CPU)
