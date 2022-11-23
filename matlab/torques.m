%% Torques %%
% Placeholder name ^^ final name TBD
% Kirk Boyd
% Created 11/18/2022
% Modified 11/20/2022
clc;clear;close all;set(0,'DefaultFigureWindowStyle','docked');set(0,'defaultTextInterpreter','latex');

%% Setup
lb = 97.7; % mm
lft = 114.28; % mm
l1 = 35.5; % mm
l2 = 76.36; % mm
l3 = 117.91; % mm
l4 = 63.86; % mm
ls_0 = 92.2; % mm
thetaC_0 = deg2rad(76); % rad % formerly theta4_0
thetaD_0 = deg2rad(49.5); % rad % formerly theta5_0
thetaE_0 = deg2rad(180) - thetaC_0 - thetaD_0; % deg % formerly theta3_0
phiE_0 = deg2rad(180) - thetaE_0;
phiA_0 = asin( (l4*sin(thetaD_0))/ls_0 );
betaC_0 = asin( (l3*sin(thetaD_0))/ls_0 );
betaC_0_check = asin( (l3*sin(phiA_0)) / l4);
phiC_0 = betaC_0 - thetaC_0;
thetaB_0 = asin( (ls_0*sin(thetaE_0)) / l1);
thetaA_0 = deg2rad(180) - thetaB_0 - thetaE_0;

%% Plot
ind = 3;
x = [0, l1]; % adds points Cx and Dx
y = [0, 0]; % adds points Cy and Dy
l_CE_0 = (ls_0 * sin(phiA_0)) / sin(phiE_0);
l_DE_0 = (l_CE_0 * sin(thetaC_0)) / sin(thetaD_0);
x(ind) = l_CE_0*cos(thetaC_0); % Ex
y(ind) = l_CE_0*sin(thetaC_0); % Ey
ind = ind+1;
% x(4) = ls_0*cos(deg2rad(180) - betaC_0); %
% y(4) = ls_0*sin(deg2rad(180) - betaC_0); % 
x(ind) = l2*cos(thetaC_0); % Bx
y(ind) = l2*sin(thetaC_0); % By
ind = ind+1;
% x(ind) = l_CE_0*cos(thetaC_0); % back to Ex
% y(ind) = l_CE_0*sin(thetaC_0); % back to Ey
% ind = ind+1;
x(ind) = ls_0*cos(deg2rad(180) - betaC_0); % Ax
y(ind) = ls_0*sin(deg2rad(180) - betaC_0); % Ay

x(length(x)+1) = x(1);
y(length(y)+1) = y(1);
plot(x,y);
hold on;
title("Fourbar");
xlabel('y (side view) [mm]');
ylabel('z (side view) [mm]');

plot(x(1),y(1),'.',MarkerSize=12);
plot(x(2),y(2),'.',MarkerSize=12);
plot(x(3),y(3),'.',MarkerSize=12);
plot(x(4),y(4),'.',MarkerSize=12);
plot(x(5),y(5),'.',MarkerSize=12);
plot(x(6),y(6),'.',MarkerSize=12);

legend("all","1","2","3","4","5","6");
%% For me to write down
thetaC_0_rad = rad2deg(thetaC_0);
thetaD_0_rad = rad2deg(thetaD_0);
thetaE_0_rad = rad2deg(thetaE_0);
phiE_0_rad = rad2deg(phiE_0);
phiA_0_rad = rad2deg(phiA_0);
betaC_0_rad = rad2deg(betaC_0);
phiC_0_rad = rad2deg(phiC_0);

