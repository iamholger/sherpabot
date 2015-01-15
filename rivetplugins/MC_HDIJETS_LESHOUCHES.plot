# BEGIN PLOT .*
RatioPlotSameStyle=1
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/cutflow
Title=Cutflow of VBF cuts
XLabel=
YLabel=$\sigma$ [pb]
XCustomMajorTicks=0	incl.	1	2jet	2	3jet	3	VBF	4	VBF-ctrl-3jet
XMin=-0.5
XMax=4.5
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/XS_H_within_tagjets
Title=Cross section for central Higgs production
XLabel=
YLabel=$\sigma$ [pb]
XCustomMajorTicks=0	2jet	1	h within	2	VBF	3	h within
XMin=-0.5
XMax=3.5
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/NJet
Title=Inclusive jet multiplicity
XLabel=$N_\text{jet}$
YLabel=$\sigma(N_\text{jet})$ [pb]
XMin=-0.5
XMax=4.5
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/H_pT
Title=Transverse momentum of the Higgs boson
XLabel=$p_\perp(h)$ [GeV]
YLabel=d$\sigma$/d$p_\perp$ [pb/GeV]
LegendXPos=0.1
LegendYPos=0.5
LogX=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/H_y
Title=Rapidity of the Higgs boson
XLabel=$y(h)$
YLabel=d$\sigma$/d$y$ [pb]
LegendXPos=0.3
LegendYPos=0.5
LogY=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/H_jet12_pT
Title=Transverse momentum of Higgs plus leading jet system
XLabel=$p_\perp(hj_1j_2)$ [GeV]
YLabel=d$\sigma$/d$p_\perp$ [pb/GeV]
LegendXPos=0.5
LegendYPos=0.75
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/H_jet12_dphi
Title=Azimuthal separation of the Higgs and the leading jet system
XLabel=$\Delta\phi(h,j_1j_2)$
YLabel=d$\sigma$/d$\Delta\phi$ [pb]
LegendXPos=0.1
LegendYPos=0.75
LogY=0
ShowZero=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/H_jet12_ystar
Title=$y^*$ of the Higgs and the leading jet system
XLabel=$|y^*(h,j_1,j_2)|$
YLabel=d$\sigma$/d$|y^*|$ [pb]
LogY=0
LegendXPos=0.5
LegendYPos=0.75
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet12_dphi
Title=Azimuthal separation of the two leading jets
XLabel=$\Delta\phi(j_1,j_2)$
YLabel=d$\sigma$/d$\Delta\phi$ [pb]
LegendXPos=0.1
LegendYPos=0.75
LogY=0
ShowZero=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet12_dy
Title=Rapidity separation of the two leading jets
XLabel=$\Delta y(j_1,j_2)$
YLabel=d$\sigma$/d$\Delta y$ [pb]
LogY=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet12_mass
Title=Invariant mass of the two tagging jets
XLabel=$m_{jj}$ [GeV]
YLabel=d$\sigma$/d$m_{jj}$ [pb/GeV]
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet1_pT
Title=Transverse momentum of leading tagjet
XLabel=$p_\perp(j_1)$ [GeV]
YLabel=d$\sigma$/d$p_\perp$ [pb/GeV]
LegendXPos=0.1
LegendYPos=0.5
LogX=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet1_y
Title=Rapidity of leading tagjet
XLabel=$y(j_1)$
YLabel=d$\sigma$/d$y$ [pb]
LegendXPos=0.3
LegendYPos=0.4
LogY=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet2_pT
Title=Transverse momentum of subleading tagjet
XLabel=$p_\perp(j_2)$ [GeV]
YLabel=d$\sigma$/d$p_\perp$ [pb/GeV]
LogX=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet2_y
Title=Rapidity of subleading tagjet
XLabel=$y(j_2)$
YLabel=d$\sigma$/d$y$ [pb]
LegendXPos=0.3
LegendYPos=0.4
LogY=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet3_pT
Title=Transverse momentum of 3rd jet
XLabel=$p_\perp(j_3)$ [GeV]
YLabel=d$\sigma$/d$p_\perp$ [pb/GeV]
LogX=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet3_y
Title=Rapidity of 3rd jet
XLabel=$y(j_3)$
YLabel=d$\sigma$/d$y$ [pb]
LegendXPos=0.3
LegendYPos=0.4
LogY=0
# END PLOT

# BEGIN PLOT /MC_HDIJETS_LESHOUCHES/jet3_ystar
Title=$y^*$ of 3rd jet
XLabel=$y^*$
YLabel=d$\sigma$/d$y^*$ [pb]
LegendXPos=0.3
LegendYPos=0.4
LogY=0
# END PLOT

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_A
\rput[lt]{0}(0.05,0.95){\bf Leading jet selection}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_B
\rput[lt]{0}(0.05,0.95){\bf Forward-backward selection}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_dijet_A
\rput[lt]{0}(0.05,0.95){\bf Leading jet selection}
\rput[lt]{0}(0.05,0.88){\bf Dijet cuts}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_VBF_A
\rput[lt]{0}(0.05,0.95){\bf Leading jet selection}
\rput[lt]{0}(0.05,0.88){\bf VBF cuts}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_dijet_B
\rput[lt]{0}(0.05,0.95){\bf Forward-backward selection}
\rput[lt]{0}(0.05,0.88){\bf Dijet cuts}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_VBF_B
\rput[lt]{0}(0.05,0.95){\bf Forward-backward selection}
\rput[lt]{0}(0.05,0.88){\bf VBF cuts}
# END SPECIAL

# BEGIN SPECIAL /MC_HDIJETS_LESHOUCHES/.*_incl
\rput[lt]{0}(0.05,0.95){\bf Inclusive event selection}
# END SPECIAL


