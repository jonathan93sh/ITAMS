F_CPU = 12000000;

T_CPU = F_CPU^-1;

ns = 10^-9;

tcs = 15*ns;
twcl =
twch =
twc  =

tdst =
tdht =



%% calc nops

tcs_NOP = ceil(tcs/T_CPU)