%% Torques %%
% Placeholder name ^^ final name TBD
% Kirk Boyd
% Created 11/18/2022
% Modified 11/20/2022
clc;clear;close all;set(0,'DefaultFigureWindowStyle','docked');set(0,'defaultTextInterpreter','latex');

%% Setup
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

% phiE is a supplamentary angle to thetaE
phiE_0 = deg2rad(180) - thetaE_0;

% Use law of Sines to find phiA from known length of its opposite side
phiA_0 = asin( (l4*sin(thetaD_0))/lsp_0 );

% % Law of Sines again for last angle in this triangle
% betaC_0 = asin( (l3*sin(thetaD_0))/lsp_0 );
% 
% % This should give the same result
% betaC_0_check = asin( (l3*sin(phiA_0)) / l4);

% So should this...
betaC_0 = deg2rad(180) - phiA_0 - thetaD_0;

% Sum of phiC and thetaC is betaC, so this gives us phiC
phiC_0 = betaC_0 - thetaC_0;

% Law of Sines for thetaB 
% thetaB_0 = asin( (lsp_0*sin(thetaE_0)) / l1); This was straight up wrong.
thetaB_0 = asin( (l_AC_0*sin(phiC_0)) / l_AB);

% Sum of angles = 180 for thetaA
thetaA_0 = deg2rad(180) - thetaB_0 - thetaE_0;

%
l_CE_0 = l_CD * ( sin(thetaD_0) / sin(thetaE_0) );
l_DE_0 = l_CD * ( sin(thetaC_0) / sin(thetaE_0) );

% clear thetaA_0 thetaB_0 thetaC_0 thetaD_0 thetaE_0 phiE_0 phiA_0 betaC_0 phiC_0

%% Plot
Cx = 0;
Cy = 0;
Dx = l4;
Dy = 0;
Ex = l_CE_0 * cos( thetaC_0 );
Ey = l_CE_0 * sin( thetaC_0 );
Bx = l_BC * cos( thetaC_0 );
By = l_BC * sin( thetaC_0 );
% Ax = -l_AC_0 * cos( deg2rad(180) - betaC_0 );
% Ay = l_AC_0 * sin( deg2rad(180) - betaC_0 );
Ax = l4 - l_AD * cos(thetaD_0);
Ay = l_AD * sin(thetaD_0);

% plot(Cx,Cy,'.',MarkerSize=12);
% hold on;
% plot(Dx,Dy,'.',MarkerSize=12);
% plot(Ex,Ey,'.',MarkerSize=12);
% plot(Ax,Ay,'.',MarkerSize=12);
% plot(Bx,By,'.',MarkerSize=12);
% plot(l4 - l_DE_0*cos(thetaD_0), l_DE_0*cos(thetaD_0));
% l_AE_0 = l_AD - l_DE_0;
% plot(Ex - l_AE_0*cos(thetaD_0),Ey + l_AE_0*sin(thetaD_0),'*');
% ind = 3;
x = [0, l4]; % adds points Cx and Dx
y = [0, 0]; % adds points Cy and Dy
x(3) = l_CE_0*cos(thetaC_0); % Ex
y(3) = l_CE_0*sin(thetaC_0); % Ey
x(4) = -lsp_0*cos(deg2rad(180) - betaC_0); % Ax
y(4) = lsp_0*sin(deg2rad(180) - betaC_0); % Ay
x(5) = l2*cos(thetaC_0); % Bx
y(5) = l2*sin(thetaC_0); % By
x(6) = l4 - l3*cos(thetaD_0);
y(6) = l3*sin(thetaD_0);
% ind = ind+1;
% x(ind) = l_CE_0*cos(thetaC_0); % back to Ex
% y(ind) = l_CE_0*sin(thetaC_0); % back to Ey
% ind = ind+1;


plot([0, l4],[0,0]);
hold on;
title("Fourbar");
xlabel('y (side view) [mm]');
ylabel('z (side view) [mm]');
plot([l4, x(3)],[0, y(3)]); % Line from D to E
plot([0,x(3)],[0,y(3)]); % Line from C to E
plot([0,x(4)],[0,y(4)]); % Line from C to A???
plot([0,x(5)],[0,y(5)]); % Line from C to B
plot([x(3),x(4)],[y(3),y(4)]); % Line from E to A
plot([l4, x(6)],[0,y(6)]); % Line from D to A

plot(x(3),y(3),'.',MarkerSize=12); % Point E
plot(x(1),y(1),'.',MarkerSize=12);
plot(x(2),y(2),'.',MarkerSize=12);
plot(x(3),y(3),'.',MarkerSize=12);
plot(x(4),y(4),'.',MarkerSize=12);
plot(x(5),y(5),'.',MarkerSize=12);
plot(x(6),y(6),'.',MarkerSize=12);
% 
% legend("all","1","2","3","4","5","6");
%% For me to write down
% thetaB_0_check_rad = rad2deg(thetaB_0_check);
thetaA_0_rad = rad2deg(thetaA_0);
thetaB_0_rad = rad2deg(thetaB_0);
thetaC_0_rad = rad2deg(thetaC_0);
thetaD_0_rad = rad2deg(thetaD_0);
thetaE_0_rad = rad2deg(thetaE_0);
phiE_0_rad = rad2deg(phiE_0);
phiA_0_rad = rad2deg(phiA_0);
betaC_0_rad = rad2deg(betaC_0);
phiC_0_rad = rad2deg(phiC_0);

