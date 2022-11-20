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
ls = 92.2; % mm
theta4_0 = 76; % deg % formerly theta4_0
theta5_0 = 49.5; % deg % formerly theta5_0
theta3_0 = 180 - theta4_0 - theta5_0; % deg % formerly theta3_0
% phi1_0 = ;
% phi2_0;

%% Plot
x = [0, l1];
y = [0, 0];
plot(x,y);
title("Fourbar");

