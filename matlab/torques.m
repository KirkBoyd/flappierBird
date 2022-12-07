%% Torques %%
% Placeholder name ^^ final name TBD
% Kirk Boyd
% Created 11/18/2022
% Modified 11/20/2022
clc;clear;close all;set(0,'DefaultFigureWindowStyle','docked');set(0,'defaultTextInterpreter','latex'); hold on;

%% Setup
% These variables can be changed 
dx = 10;
dt = 0.1;
k = 800; % N/m
dataLength = dx/dt;
endTime = 1; % sec

% This is where we place the COG of the bird relative to point A on the
% fourbar
x_COG_bird = 120 * 10^(-3); % mm -> m
y_COG_bird = 70 * 10^(-3); % mm -> m

%% Constant Lengths
lb = 98; % mm % theoretical: 
lft = 4.5*25.4; % mm % theoretical:
l_AB = 36; % mm % theoretical: 35.243mm from CAD
l_BC = 77; % mm % theoretical: 76.2mm from CAD
l_AD = 118; % mm % theoretical: 118.682mm from CAD
l_CD = 64; % mm % theoretical: 63.5mm from CAD
% Also define them by their endpoints for checking our answers
% l_AB = l1;
% l_BC = l2;
% l_AD = l3;
% l_CD = l4;
% Exact Values from CAD if we want them
% l_AB = 35.243;
% l_BC = 76.2;
% l_AD = 118.682;
% l_CD = 63.697;

%% Initial Conditions
thetaB_0 = deg2rad(89.999);

lsp_0 = sqrt( l_AB^2 + l_BC^2 - 2*l_AB*l_BC*cos(thetaB_0) );
phiC_0 = asin( (l_AB*sin(thetaB_0)) / lsp_0 );
betaA_0 = deg2rad(180) - thetaB_0 - phiC_0;
phiA_0 = acos( (lsp_0^2 + l_AD^2 - l_CD^2)/(2*lsp_0*l_AD) );
thetaA_0 = betaA_0 - phiA_0;
thetaE_0 = deg2rad(180) - thetaB_0 - thetaA_0;
thetaD_0 = asin( (lsp_0*sin(phiA_0)) / l_CD );
betaC_0 = deg2rad(180) - thetaD_0 - phiA_0;
thetaC_0 = betaC_0 - phiC_0;
phiE_0 = deg2rad(180) - thetaE_0;

% % Dynamic Lengths from Measurement
% lsp_0 = 92; % mm
% l_AC_0 = lsp_0;
% 
% % Measured Angles
% thetaC_0 = deg2rad(76); % rad % formerly theta4_0
% thetaD_0 = deg2rad(50); % rad % formerly theta5_0
% 
% % Calculate Other Angles
% % Using only sum of angles in triangle = 180
% thetaE_0 = deg2rad(180) - thetaC_0 - thetaD_0; % deg % formerly theta3_0
% phiE_0 = deg2rad(180) - thetaE_0;% phiE is a supplamentary angle to thetaE
% 
% % Use law of Sines to find phiA from known length of its opposite side
% phiA_0 = asin( (l_CD*sin(thetaD_0))/lsp_0 );
% betaC_0 = deg2rad(180) - phiA_0 - thetaD_0;
% 
% % Sum of phiC and thetaC is betaC, so this gives us phiC
% phiC_0 = betaC_0 - thetaC_0;
% 
% % Law of Sines for thetaB 
% thetaB_0 = asin( (l_AC_0*sin(phiC_0)) / l_AB);
% 
% % Sum of angles = 180 for thetaA
% thetaA_0 = deg2rad(180) - thetaB_0 - thetaE_0;
% betaA_0 = phiA_0 + thetaA_0;
% 
% % Calculate line to instant center
% l_CE_0 = l_CD * ( sin(thetaD_0) / sin(thetaE_0) );
% l_DE_0 = l_CD * ( sin(thetaC_0) / sin(thetaE_0) );
% l_AE_0 = l_AD - l_DE_0;
% l_BE_0 = l_BC - l_CE_0;

% clear thetaA_0 thetaB_0 thetaC_0 thetaD_0 thetaE_0 phiE_0 phiA_0 betaC_0 phiC_0
%% Plot
Ax =  0;
Ay =  0;
Bx =  l_AB;
By =  0;
Cx =  lsp_0 * cos(thetaA_0 + phiA_0);
Cy = -lsp_0 * sin(thetaA_0 + phiA_0);
Dx =  l_AD*cos(thetaA_0);
Dy = -l_AD*sin(thetaA_0);
% Ex =  l_AE_0*cos(thetaA_0);
% Ey = -l_AE_0*sin(thetaA_0);

x(1) = Ax;  y(1) = Ay;
x(2) = Bx;  y(2) = By;
x(3) = Cx;  y(3) = Cy;
x(4) = Dx;  y(4) = Dx;
% x(5) = Ex;  y(5) = Ey;

plot(Ax,Ay,'.k',MarkerSize=12); % plot point A
plot(Bx,By,'.k',MarkerSize=12); % plot point B
plot(Cx,Cy,'.k',MarkerSize=12); % plot point C
plot(Dx,Dy,'.k',MarkerSize=12); % plot point D
% plot(Ex,Ey,'.k',MarkerSize=12); % plot point E


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

% %% replace the values bc lazy
% phiC_0 = acos( (lsp_0^2 + l_BC^2 - l_AB^2) / (2*lsp_0*l_BC));
% thetaB_0 = asin( ( lsp_0 * sin(phiC_0) ) / l_AB );
% betaA_0 = deg2rad(180) - phiC_0 - thetaB_0;
% phiA_0 = acos( (lsp_0^2 + l_AD^2 - l_CD^2) / (2*lsp_0*l_AD));
% thetaA_0 = betaA_0 - phiA_0;
% thetaD_0 = asin( (  lsp_0 * sin(phiA_0) ) / l_CD );
% betaC_0 = deg2rad(180) - phiA_0 - thetaD_0;
% thetaC_0 = betaC_0 - phiC_0;
% phiE_0 = deg2rad(180) - phiA_0 - phiC_0;
% thetaE_0 = deg2rad(180) - phiE_0;
% Bx =  l1;
% By =  0;
% Cx =  lsp_0 * cos(thetaA_0 + phiA_0);
% Cy = -lsp_0 * sin(thetaA_0 + phiA_0);
% Dx =  l_AD*cos(thetaA_0);
% Dy = -l_AD*sin(thetaA_0);
% Ex =  l_AE_0*cos(thetaA_0);
% Ey = -l_AE_0*sin(thetaA_0);
% 
% x(1) = Ax;  y(1) = Ay;
% x(2) = Bx;  y(2) = By;
% x(3) = Cx;  y(3) = Cy;
% x(4) = Dx;  y(4) = Dx;
% x(5) = Ex;  y(5) = Ey;
% 
% plot(Ax,Ay,'.k',MarkerSize=12); % plot point A
% plot(Bx,By,'.g',MarkerSize=12); % plot point B
% plot(Cx,Cy,'.y',MarkerSize=12); % plot point C
% plot(Dx,Dy,'.k',MarkerSize=12); % plot point D
% plot(Ex,Ey,'.k',MarkerSize=12); % plot point E

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
betaA_F = thetaA_F + phiA_F;

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
% plot(Ex,Ey,'.r',MarkerSize=12); % plot point E



% %% Calculate every time step
%% Initialize arrays
% Preallocate lsp
lsp = zeros(dataLength,2);
% Assign increasing time step to each row of array
lsp(:,1) = linspace(0,endTime,dataLength);
% All arrays will have this in the first column, so preallocate every
% matrix to match
thetaA = lsp;
thetaB = thetaA;
thetaC = thetaA;
thetaD = thetaA;
thetaE = thetaA;
phiA = thetaA;
phiC = thetaA;
phiE = thetaA;
betaC = thetaA;
betaA = lsp;

thetaA_check = lsp;
thetaB_check = thetaA;
thetaC_check = thetaA;
thetaD_check = thetaA;
thetaE_check = thetaA;
phiA_check = thetaA;
phiC_check = thetaA;
phiE_check = thetaA;
betaC_check = thetaA;
betaA_check = thetaA;
l_CE_check = thetaA;
l_BE_check = thetaA;

% Put in initial values
thetaA(1,2) = thetaA_0;
thetaB(1,2) = thetaB_0;
thetaC(1,2) = thetaC_0;
thetaD(1,2) = thetaD_0;
thetaE(1,2) = thetaE_0;
phiA(1,2)   = phiA_0;
phiC(1,2)   = phiC_0;
phiE(1,2)   = phiE_0;
betaC(1,2)  = betaC_0;
betaA(1,2)  = betaA_0;

% Put in final values
thetaA(length(thetaA) , 2) = thetaA_F;
thetaB(length(thetaB) , 2) = thetaB_F;
thetaC(length(thetaC) , 2) = thetaC_F;
thetaD(length(thetaD) , 2) = thetaD_F;
thetaE(length(thetaE) , 2) = thetaE_F;
phiA(length(phiA) , 2)   = phiA_F;
phiC(length(phiC) , 2)   = phiC_F;
phiE(length(phiE) , 2)   = phiE_F;
betaA(length(betaA),2)   = betaA_F;

% Evenly space each change in length for each time step
lsp(:,2) = linspace(lsp_0,lsp_F,dataLength);

% Put in time steps
thetaA(:,1) = linspace(0,endTime,dataLength);
thetaA(:,2) = linspace(thetaA_0,thetaA_F,dataLength);

phiA(:,1) = thetaA(:,1);
phiA(:,2) = linspace(phiA_0,phiA_F,dataLength);
phiC(:,2) = linspace(phiC_0,phiC_F,dataLength);
thetaB(:,2) = linspace(thetaB_0,thetaB_F,dataLength);
betaA(:,2) = linspace(betaA_0,betaA_F,dataLength);

%% Fully calculate everything based on length of spring
% phiC_0_check = acos( (lsp_0^2 + l_BC^2 - l_AB^2) / (2*lsp_0*l_BC));
% phiA_0_check = acos( (lsp_0^2 + l_AD^2 - l_CD^2) / (2*lsp_0*l_AD));
% thetaD_0_check = asin( (  lsp_0 * sin(phiA_0_check) ) / l_CD );
% betaC_0_check = deg2rad(180) - phiA_0_check - thetaD_0_check;
% thetaC_0_check = betaC_0_check - phiC_0_check;
% phiE_0_check = deg2rad(180) - phiA_0_check - phiC_0_check;
% thetaE_0_check = deg2rad(180) - phiE_0_check;
% l_CE_0_check = (l_CD * sin(thetaD_0_check)) / sin(thetaE_0_check);
% l_BE_0_check = l_BC - l_CE_0_check;
% thetaA_0_check = asin( (l_BE_0_check * sin(thetaE_0_check)) / l_AB );
% betaA_0_check = phiA_0_check + thetaA_0_check;
% thetaB_0_check = deg2rad(180) - phiC_0_check - betaA_0_check;

% betaA_0_check = asin( ( l_BC * sin(phiC_0_check) ) / l_AB );
% thetaA_0_check = betaA_0_check - phiA_0_check;


phiC(:,2) = acos( (lsp(:,2).^2 + l_BC^2 - l_AB^2) ./ (2*lsp(:,2).*l_BC));
phiA(:,2) = acos( (lsp(:,2).^2 + l_AD^2 - l_CD^2) ./ (2*lsp(:,2).*l_AD));
thetaD(:,2) = asin( (  lsp(:,2) .* sin(phiA(:,2)) ) ./ l_CD );
betaC(:,2) = deg2rad(180) - phiA(:,2) - thetaD(:,2);
thetaC(:,2) = betaC(:,2) - phiC(:,2);
phiE(:,2) = deg2rad(180) - phiA(:,2) - phiC(:,2);
thetaE(:,2) = deg2rad(180) - phiE(:,2);
l_CE(:,2) = (l_CD .* sin(thetaD(:,2))) ./ sin(thetaE(:,2));
l_BE(:,2) = l_BC - l_CE(:,2);
thetaA(:,2) = asin( (l_BE(:,2) .* sin(thetaE(:,2))) ./ l_AB );
betaA(:,2) = phiA(:,2) + thetaA(:,2);
thetaB(:,2) = deg2rad(180) - phiC(:,2) - betaA(:,2);


% betaA_check(:,2) = asin( ( l_BC .* sin(phiC_check(:,2)) ) ./ l_AB );
% thetaA_check(:,2) = betaA_check(:,2) - phiA_check(:,2);





%% SOMETHING IS WRONG WITH WHICH VALUE OF ASIN IS SELECTED, THATS WHY IT JUMPS

%% Locate the points in cartesian space
A = ones(dataLength,2)*Ax; % Point A is always (0,0)
% A_check = A;
B = ones(dataLength,2);
B(:,1) = Bx; % Point B is grounded
B(:,2) = By; % Point B is grounded
% B_check = B;
C = ones(dataLength,2);
D = C;
E = C;
% C_check = C;
% D_check = D;
% E_check = E;

for i = 1 : dataLength
    if ( thetaA(i,2) + phiA(i,2) ) > deg2rad(90)
        C(i,1) = lsp(i,2)*cos( thetaA(i,2) + phiA(i,2) );
        C(i,2) = -lsp(i,2)*sin( thetaA(i,2) + phiA(i,2) );
    else
        C(i,1) = -lsp(i,2)*cos( deg2rad(180) - thetaA(i,2) - phiA(i,2) );
        C(i,2) = -lsp(i,2)*sin( deg2rad(180) - thetaA(i,2) - phiA(i,2) );
    end
%     if ( thetaA_check(i,2) + phiA_check(i,2) ) > deg2rad(90)
%         C_check(i,1) = lsp(i,2)*cos( thetaA_check(i,2) + phiA_check(i,2) );
%         C_check(i,2) = -lsp(i,2)*sin( thetaA_check(i,2) + phiA_check(i,2) );
%     else
%         C_check(i,1) = -lsp(i,2)*cos( deg2rad(180) - thetaA_check(i,2) - phiA_check(i,2) );
%         C_check(i,2) = -lsp(i,2)*sin( deg2rad(180) - thetaA_check(i,2) - phiA_check(i,2) );
%     end

end % end main for loop
D(:,1) = l_AD*cos(thetaA(:,2));
D(:,2) = -l_AD*sin(thetaA(:,2));
% D_check(:,1) = l_AD*cos(thetaA_check(:,2));
% D_check(:,2) = -l_AD*sin(thetaA_check(:,2));

%% Plot path of point
plot(C(:,1),C(:,2),':b');
plot(D(:,1),D(:,2),':c');
% plot(C_check(:,1),C_check(:,2),':b');
% plot(D_check(:,1),D_check(:,2),':c');

% plot(A_check(1,1),A_check(1,2),'.y',MarkerSize=12); % plot point A
% plot(B_check(1,1),B_check(1,2),'.y',MarkerSize=12); % plot point B
% plot(C_check(1,1),C_check(1,2),'.y',MarkerSize=12); % plot point C
% plot(D_check(1,1),D_check(1,2),'.y',MarkerSize=12); % plot point D
% plot(E_check(1,1),E_check(1,2),'.y',MarkerSize=12); % plot point E
% 
% plot(A_check(length(A_check),1),A_check(length(A_check),2),'.',MarkerSize=12); % plot point A
% plot(B_check(length(B_check),1),B_check(length(B_check),2),'.g',MarkerSize=12); % plot point B
% plot(C_check(length(C_check),1),C_check(length(C_check),2),'.b',MarkerSize=12); % plot point C
% plot(D_check(length(D_check),1),D_check(length(D_check),2),'.c',MarkerSize=12); % plot point D
% plot(E_check(length(E_check),1),E_check(length(E_check),2),'.m',MarkerSize=12); % plot point E

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

%% Forces
deltaL = lsp(1,2) - lsp(2,2);
% betaA = thetaA(:,2) + phiA(:,2);
F_AD = ( k*deltaL*sin(betaA) ) ./ sin(thetaA(:,2));
F_BC = ( k*deltaL*cos(betaA) + F_AD.*cos(thetaA(:,2)) ) ./ cos(thetaB(:,2));


%% LEGEND
legend("A","B","C","D","E(a)" ...
    );
%     "AB_0","lsp_0","AD_0","BC_0","CD_0", ...
    ... %"E(c)","E(b)", ...
%     "AC_F","lsp_f","BC_F","AD_F","BD_F");

% %%
% figure(); hold on;
% plot(lsp(:,1),lsp(:,2));
% plot(phiC(:,1), rad2deg(phiC(:,2)) );
% plot(phiC_check(:,1), rad2deg(phiC_check(:,2)) );
% plot(phiA(:,1), rad2deg(phiA(:,2)) );
% plot(phiA_check(:,1), rad2deg(phiA_check(:,2)) );
% % legend();
% % figure(); hold on;
% plot( thetaB(:,1) , rad2deg( thetaB(:,2) ) );
% % plot( thetaB_check(:,1) , rad2deg( thetaB_check(:,2) ) );
% plot(betaA(:,1), rad2deg(betaA(:,2)) );
% plot(betaA_check(:,1), rad2deg(betaA_check(:,2)) );
% legend("lsp","phiA","phiA _ check","phiC","phiC _ check","thetaB","thetaB _ check","betaA","betaA_check",Location="northwest"); %,"test");
% figure(); hold on;
% plot(lsp(:,1),( (lsp(:,2).^2 + l_BC^2 - l_AB^2) ./ (2*lsp(:,2).*l_BC)));
% plot(thetaA(:,1),thetaA(:,2));
% plot(thetaA_check(:,1),thetaA_check(:,2));
%% Graveyard
    % plot(D(1,1),D(1,2),'*');
    % plot([0, l_AD*cos(thetaA_0)],[0, -l_AD*sin(thetaA_0)]);
    % plot([0, l_AD*cos(thetaA(1,2))],[0, -l_AD*sin(thetaA(1,2))]);
% had to use this ^^^ to find that I was plotting point D_0 using thetaE
% instead of thetaA 