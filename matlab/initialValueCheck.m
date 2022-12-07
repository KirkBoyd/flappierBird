%% Initial Value Check %%
% Placeholder name ^^ final name TBD
% Kirk Boyd
% Created 11/18/2022
% Modified 11/20/2022
clc;clear;close all;set(0,'DefaultFigureWindowStyle','docked');set(0,'defaultTextInterpreter','latex'); %hold on;

lb = 98;
lft = 4.5*25.4;%???
l_AB = 35.243;
l_BC = 76.2;
l_AD = 118.682;
l_CD = 63.5;
thetaB = deg2rad(89.999);
% thetaB = deg2rad(110);

lsp = sqrt(l_AB^2 + l_BC^2 - 2*l_AB*l_BC*cos(thetaB));
phiC = asin( (l_AB*sin(thetaB)) / lsp ) ;
betaA = deg2rad(180) - thetaB - phiC;
phiA = acos( (lsp^2 + l_AD^2 - l_CD^2)/(2*lsp*l_AD) );
thetaA = betaA - phiA;
thetaE = deg2rad(180) - thetaB - thetaA;
thetaD = asin( (lsp*sin(phiA)) / l_CD );
betaC = deg2rad(180) - thetaD - phiA;
thetaC = betaC - phiC;
phiE = deg2rad(180) - thetaE;

%%
thetaA_deg = rad2deg(thetaA);
thetaB_deg = rad2deg(thetaB);
thetaC_deg = rad2deg(thetaC);
thetaD_deg = rad2deg(thetaD);
thetaE_deg = rad2deg(thetaE);
phiA_deg = rad2deg(phiA);
phiC_deg = rad2deg(phiC);
phiE_deg = rad2deg(phiE);
betaA_deg = rad2deg(betaA);
betaC_deg = rad2deg(betaC);