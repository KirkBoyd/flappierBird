%% Torques %%
% Placeholder name ^^ final name TBD
% Kirk Boyd
% Created 11/18/2022
% Modified 11/20/2022
clc;clear;close all;set(0,'DefaultFigureWindowStyle','docked');set(0,'defaultTextInterpreter','latex'); hold on;

%% Setup
dx = 10;
dt = 0.1;
dataLength = dx/dt;
endTime = 1; % sec

%% Constant Lengths
lb = 98; % mm
lft = 4.5*25.4; % mm
l1 = 36; % mm
l2 = 77; % mm
l3 = 118; % mm
l4 = 64; % mm
% Also define them by their endpoints for checking our answers
l_AB = l1;
l_BC = l2;
l_AD = l3;
l_CD = l4;

%% Initial Conditions
% Dynamic Lengths from Measurement
lsp_0 = 92; % mm
l_AC_0 = lsp_0;

% Measured Angles
thetaC_0 = deg2rad(76); % rad % formerly theta4_0
thetaD_0 = deg2rad(50); % rad % formerly theta5_0

% Calculate Other Angles
% Using only sum of angles in triangle = 180
thetaE_0 = deg2rad(180) - thetaC_0 - thetaD_0; % deg % formerly theta3_0
phiE_0 = deg2rad(180) - thetaE_0;% phiE is a supplamentary angle to thetaE

% Use law of Sines to find phiA from known length of its opposite side
phiA_0 = asin( (l4*sin(thetaD_0))/lsp_0 );
betaC_0 = deg2rad(180) - phiA_0 - thetaD_0;

% Sum of phiC and thetaC is betaC, so this gives us phiC
phiC_0 = betaC_0 - thetaC_0;

% Law of Sines for thetaB 
thetaB_0 = asin( (l_AC_0*sin(phiC_0)) / l_AB);

% Sum of angles = 180 for thetaA
thetaA_0 = deg2rad(180) - thetaB_0 - thetaE_0;

% Calculate line to instant center
l_CE_0 = l_CD * ( sin(thetaD_0) / sin(thetaE_0) );
l_DE_0 = l_CD * ( sin(thetaC_0) / sin(thetaE_0) );
l_AE_0 = l_AD - l_DE_0;
l_BE_0 = l_BC - l_CE_0;

% clear thetaA_0 thetaB_0 thetaC_0 thetaD_0 thetaE_0 phiE_0 phiA_0 betaC_0 phiC_0

%% Plot
Ax =  0;
Ay =  0;
Bx =  l1;
By =  0;
Cx =  lsp_0 * cos(thetaA_0 + phiA_0);
Cy = -lsp_0 * sin(thetaA_0 + phiA_0);
Dx =  l3*cos(thetaA_0);
Dy = -l3*sin(thetaA_0);
Ex =  l_AE_0*cos(thetaA_0);
Ey = -l_AE_0*sin(thetaA_0);

x(1) = Ax;  y(1) = Ay;
x(2) = Bx;  y(2) = By;
x(3) = Cx;  y(3) = Cy;
x(4) = Dx;  y(4) = Dx;
x(5) = Ex;  y(5) = Ey;

plot(Ax,Ay,'.k',MarkerSize=12); % plot point A
plot(Bx,By,'.g',MarkerSize=12); % plot point B
plot(Cx,Cy,'.b',MarkerSize=12); % plot point C
plot(Dx,Dy,'.c',MarkerSize=12); % plot point D
plot(Ex,Ey,'.m',MarkerSize=12); % plot point E


title("Fourbar");
xlabel('y (side view) [mm]');
ylabel('z (side view) [mm]');
xlim([-50, 150]);
ylim([-150, 50]);

plot([Ax, Bx],[Ay, By],'--k'); % plot l1 / l_AB
plot([Ax, Cx],[Ay, Cy],'--r'); % plot lsp / l_AC
plot([Ax, Dx],[Ay, Dy],'--c'); % plot l3 / l_AD
plot([Bx, Cx],[By, Cy],'--g'); % plot l2 / l_BC
plot([Cx, Dx],[Cy, Dy],'--b'); % plot l4 / l_CD

% plot(Cx + l_CE_0*cos(thetaC_0), Cy + l_CE_0*sin(thetaC_0),'.',MarkerSize=12);
% plot(Bx - l_BE_0*cos(thetaB_0), By - l_BE_0*sin(thetaB_0),'*',MarkerSize=12);



%% Maximum Conditions
lsp_F = 56; % mm
% Measured Angles
thetaA_F = deg2rad(105); % rad
thetaB_F = deg2rad(40); % rad
thetaC_F = deg2rad(140); % rad

% Calculate other Angles
thetaE_F = deg2rad(180) - thetaB_F - thetaA_F;
thetaD_F = deg2rad(180) - thetaE_F - thetaC_F;
phiE_F = deg2rad(180) - thetaE_F;
phiC_F = asin( (l_AB * sin(phiE_F))/lsp_F );
phiA_F = deg2rad(180) - phiC_F - phiE_F;

% Calculate lines to instant center
l_CE_F = l_CD * ( sin(thetaD_F) / sin(thetaE_F) );
l_DE_F = l_CD * ( sin(thetaC_F) / sin(thetaE_F) );
l_AE_F = l_AD - l_DE_F;
l_BE_F = l_BC - l_CE_F;

%% Plot Final Position
Cx = -lsp_F*cos( deg2rad(180) - thetaA_F - phiA_F );
Cy = -lsp_F*sin( deg2rad(180) - thetaA_F - phiA_F );
Dx = -l_AD*cos( deg2rad(180) - thetaA_F );
Dy = -l_AD*sin( deg2rad(180) - thetaA_F );

plot([Ax, Bx],[Ay, By],'--k'); % plot l1 / l_AB
plot([Ax, Cx],[Ay, Cy],'--r'); % plot lsp / l_AC
plot([Ax, Dx],[Ay, Dy],'--c'); % plot l3 / l_AD
plot([Bx, Cx],[By, Cy],'--g'); % plot l2 / l_BC
plot([Cx, Dx],[Cy, Dy],'--b'); % plot l4 / l_CD

plot(Ax,Ay,'.k',MarkerSize=12); % plot point A
plot(Bx,By,'.g',MarkerSize=12); % plot point B
plot(Cx,Cy,'.b',MarkerSize=12); % plot point C
plot(Dx,Dy,'.c',MarkerSize=12); % plot point D
plot(Ex,Ey,'.m',MarkerSize=12); % plot point E

legend("A","B","C","D","E(a)", ...
    "AB_0","lsp_0","AD_0","BC_0","CD_0", ...
    ... %"E(c)","E(b)", ...
    "AC_F","lsp_f","BC_F","AD_F","BD_F");

%% Calculate every time step
% Initialize arrays
lsp = zeros(dataLength,2);
thetaA = zeros(dataLength,2);
thetaB = thetaA;
thetaC = thetaA;
thetaD = thetaA;
thetaE = thetaA;
phiA = thetaA;
phiC = thetaA;
phiE = thetaA;
betaC = thetaA;

% Put in initial values

% thetaA(1,2) = thetaA_0;
thetaB(1,2) = thetaB_0;
thetaC(1,2) = thetaC_0;
thetaD(1,2) = thetaD_0;
thetaE(1,2) = thetaE_0;
phiA(1,2)   = phiA_0;
phiC(1,2)   = phiC_0;
phiE(1,2)   = phiE_0;
betaC(1,2)  = betaC_0;

% Put in final values
% thetaA(length(thetaA) , 2) = thetaA_F;
thetaB(length(thetaB) , 2) = thetaB_F;
thetaC(length(thetaC) , 2) = thetaC_F;
thetaD(length(thetaD) , 2) = thetaD_F;
thetaE(length(thetaE) , 2) = thetaE_F;
phiA(length(phiA) , 2)   = phiA_F;
phiC(length(phiC) , 2)   = phiC_F;
phiE(length(phiE) , 2)   = phiE_F;

% Put in time steps
thetaA(:,1) = linspace(0,endTime,dataLength);
thetaA(:,2) = linspace(thetaA_0,thetaA_F,dataLength);
lsp(:,1) = linspace(0,endTime,dataLength);
lsp(:,2) = linspace(lsp_0,lsp_F,dataLength);
phiA(:,1) = thetaA(:,1);
phiA(:,2) = linspace(phiA_0,phiA_F,dataLength);

A = ones(dataLength,2)*Ax; % Point A is always (0,0)
B = ones(dataLength,2);
B(:,1) = Bx; % Point B is grounded
b(:,2) = By; % Point B is grounded
C = ones(dataLength,2);
D = C;
E = C;

for i = 1 : dataLength
    if ( thetaA(i,2) + phiA(i,2) ) > deg2rad(90)
        C(i,1) = lsp(i,2)*cos( thetaA(i,2) + phiA(i,2) );
        C(i,2) = -lsp(i,2)*sin( thetaA(i,2) + phiA(i,2) );
    else
        C(i,1) = -lsp(i,2)*cos( deg2rad(180) - thetaA(i,2) - phiA(i,2) );
        C(i,2) = -lsp(i,2)*sin( deg2rad(180) - thetaA(i,2) - phiA(i,2) );
    end


end % end main for loop
D(:,1) = l_AD*cos(thetaA(:,2));
D(:,2) = -l_AD*sin(thetaA(:,2));
%% Plot path of point
plot(C(:,1),C(:,2),':b');
plot(D(:,1),D(:,2),':c');
%% For me to write down
% thetaB_0_check_rad = rad2deg(thetaB_0_check);
thetaA_0_deg = rad2deg(thetaA_0);
thetaB_0_deg = rad2deg(thetaB_0);
thetaC_0_deg = rad2deg(thetaC_0);
thetaD_0_deg = rad2deg(thetaD_0);
thetaE_0_deg = rad2deg(thetaE_0);
phiE_0_deg = rad2deg(phiE_0);
phiA_0_deg = rad2deg(phiA_0);
betaC_0_deg = rad2deg(betaC_0);
phiC_0_deg = rad2deg(phiC_0);


%% Graveyard
    % plot(D(1,1),D(1,2),'*');
    % plot([0, l_AD*cos(thetaA_0)],[0, -l_AD*sin(thetaA_0)]);
    % plot([0, l_AD*cos(thetaA(1,2))],[0, -l_AD*sin(thetaA(1,2))]);
% had to use this ^^^ to find that I was plotting point D_0 using thetaE
% instead of thetaA 