#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import wx
import os
import shutil
import commands

class Example(wx.Frame):
  
    def __init__(self, parent, title):
        super(Example, self).__init__(parent, title=title, 
            size=(900, 700))
            
        self.InitUI()
        self.Centre()
        self.Show()     
        
    def InitUI(self):
    
        panel = wx.Panel(self)
        
        font = wx.SystemSettings_GetFont(wx.SYS_SYSTEM_FONT)
        font.SetPointSize(9)
        font2 = wx.Font(10, wx.DEFAULT, wx.NORMAL, wx.BOLD)

        vbox = wx.BoxSizer(wx.VERTICAL)

        hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        #file1
        heading1 = wx.StaticText(panel , wx.ID_ANY, label='File 1: ')
        heading1.SetFont(font2)
        hbox1.Add(heading1)
        self.tc1 = wx.TextCtrl(panel)
        hbox1.Add(self.tc1, proportion=1)
        btn1 = wx.Button(panel, wx.ID_ANY ,'Brouse', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnBrouse1, id=btn1.GetId())
        hbox1.Add(btn1)
        vbox.Add(hbox1, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)

        #file2
        heading2 = wx.StaticText(panel , wx.ID_ANY, label='File 2: ')
        heading2.SetFont(font2)
        hbox1.Add(heading2)
        self.tc2 = wx.TextCtrl(panel)
        hbox1.Add(self.tc2, proportion=1)
        btn2 = wx.Button(panel, wx.ID_ANY ,'Brouse', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnBrouse2, id=btn2.GetId())
        hbox1.Add(btn2)

        vbox.Add((-1, 10))


        checkbtn = wx.Button(panel, wx.ID_ANY ,'Check', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnCheck, id=checkbtn.GetId())
        hbox1.Add(checkbtn)
        vbox.Add((-1, 10))
        
        
        #directory
        hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        heading3 = wx.StaticText(panel , wx.ID_ANY, label='Directory: ')
        heading3.SetFont(font2)
        hbox4.Add(heading3)
        self.tc3 = wx.TextCtrl(panel)
        hbox4.Add(self.tc3, proportion=1)
        btn3 = wx.Button(panel, wx.ID_ANY ,'Brouse', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnBrouse3, id=btn3.GetId())
        hbox4.Add(btn3)
        vbox.Add(hbox4, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)

        vbox.Add((-1, 10))
        
        checkbtn2 = wx.Button(panel, wx.ID_ANY ,'Check', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnCheck2, id=checkbtn2.GetId())
        hbox4.Add(checkbtn2)
        
        #Multifile Assignment
        hbox10 = wx.BoxSizer(wx.HORIZONTAL)
        heading5 = wx.StaticText(panel , wx.ID_ANY, label='Multifile Assignment Directory: ')
        heading5.SetFont(font2)
        hbox10.Add(heading5)
        self.tc4 = wx.TextCtrl(panel)
        hbox10.Add(self.tc4, proportion=1)
        btn4 = wx.Button(panel, wx.ID_ANY ,'Brouse', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnBrouse4, id=btn4.GetId())
        hbox10.Add(btn4)
        vbox.Add(hbox10, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)

        vbox.Add((-1, 10))
        
        checkbtn3 = wx.Button(panel, wx.ID_ANY ,'Check', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnCheck3, id=checkbtn3.GetId())
        hbox10.Add(checkbtn3)
        
        #Similarity Threshold
        hbox9 = wx.BoxSizer(wx.HORIZONTAL)
        heading4 = wx.StaticText(panel , wx.ID_ANY, label='Similarity(0-1) Default = 0.7: ')
        heading4.SetFont(font2)
        hbox9.Add(heading4)
        self.simthrestc = wx.TextCtrl(panel)
        hbox9.Add(self.simthrestc)
        vbox.Add(hbox9 , flag=wx.ALIGN_RIGHT|wx.RIGHT, border=10)
        
        #Results
        hbox3 = wx.BoxSizer(wx.HORIZONTAL)
        self.resulttc = wx.TextCtrl(panel , style=wx.TE_MULTILINE|wx.TE_READONLY , size=(100,200))
        hbox3.Add(self.resulttc, proportion=1)
        vbox.Add(hbox3, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)
        
        hbox7 = wx.BoxSizer(wx.HORIZONTAL)
        closebtn = wx.Button(panel, wx.ID_ANY ,'Close', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnExit, id=closebtn.GetId())
        hbox7.Add(closebtn, flag=wx.LEFT|wx.BOTTOM, border=5)
        clearbtn = wx.Button(panel, wx.ID_ANY ,'Clear', size=(70, 30))
        self.Bind(wx.EVT_BUTTON,  self.OnClear, id=clearbtn.GetId())
        hbox7.Add(clearbtn, flag=wx.LEFT|wx.BOTTOM, border=5)
        vbox.Add(hbox7, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)
        
        hbox8 = wx.BoxSizer(wx.HORIZONTAL)
        slogen = wx.StaticText(panel , wx.ID_ANY, label='*** CHEATING IS A CHOICE NOT A MISTAKE ***')
        slogen.SetFont(font2)
        hbox8.Add(slogen)
        vbox.Add(hbox8, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=10)

        panel.SetSizer(vbox)

    def OnBrouse1(self, event):
        dlg = wx.FileDialog(self, "Choose a file", os.getcwd(), "", "*.*", wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
                path = dlg.GetPath()
                #mypath = os.path.basename(path)
                self.tc1.Clear()
                self.tc1.AppendText( path)
       
        dlg.Destroy()
        
    def OnBrouse2(self, event):
        dlg = wx.FileDialog(self, "Choose a file", os.getcwd(), "", "*.*", wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
                path = dlg.GetPath()
                #mypath = os.path.basename(path)
                self.tc2.Clear()
                self.tc2.AppendText( path)
       
        dlg.Destroy()
    
    def OnBrouse3(self, event):
        dlg = wx.DirDialog(self, "Choose a directory:", style=wx.DD_DEFAULT_STYLE | wx.DD_NEW_DIR_BUTTON)
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPath()
            self.tc3.Clear()
            self.tc3.AppendText(path)
        dlg.Destroy()
    
    def OnBrouse4(self, event):
        dlg = wx.DirDialog(self, "Choose a directory:", style=wx.DD_DEFAULT_STYLE | wx.DD_NEW_DIR_BUTTON)
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPath()
            self.tc4.Clear()
            self.tc4.AppendText(path)
        dlg.Destroy()
    
    def OnCheck(self , event):
        path1 = self.tc1.GetValue()
        path2 = self.tc2.GetValue()
        if (not path1) or (not path2):
            self.resulttc.Clear()
            self.resulttc.AppendText("Supply two files")
            return
        try:
            simth = float(self.simthrestc.GetValue())
        except ValueError:
            simth = 0.7
            
        if simth <= 0 or simth > 1:
            simth = 0.7
        
        if path1 == path2:
            self.resulttc.Clear()
            self.resulttc.AppendText("Both files are same")
            return
        cmd = "bash FindSim.sh " + path1 + " " + path2 + " " + str(simth)
        #print cmd
        self.resulttc.Clear()
        (status , output) = commands.getstatusoutput(cmd)
        if status:
            sys.stderr.write("There was an error : " + output)
            self.resulttc.AppendText("There was an error : " + output)
            sys.exit(1)
        self.resulttc.AppendText( output)
        
    def OnCheck2(self , event):
        path1 = self.tc3.GetValue()
        if not path1:
            self.resulttc.Clear()
            self.resulttc.AppendText("Supply a directory")
            return
        try:
            simth = float(self.simthrestc.GetValue())
        except ValueError:
            simth = 0.7
            
        if simth <= 0 or simth > 1:
            simth = 0.7
        cmd = "bash directory.sh " + path1 + " " + str(simth)
        #print cmd
        self.resulttc.Clear()
        (status , output) = commands.getstatusoutput(cmd)
        if status:
            sys.stderr.write("There was an error : " + output)
            self.resulttc.AppendText("There was an error : " + output)
            sys.exit(1)
        self.resulttc.AppendText( output)
    
    def OnCheck3(self , event):
        path1 = self.tc4.GetValue()
        if not path1:
            self.resulttc.Clear()
            self.resulttc.AppendText("Supply a directory")
            return
        try:
            simth = float(self.simthrestc.GetValue())
        except ValueError:
            simth = 0.7
            
        if simth <= 0 or simth > 1:
            simth = 0.7
        cmd = "bash directoryas.sh " + path1 + " " + str(simth)
        #print cmd
        self.resulttc.Clear()
        (status , output) = commands.getstatusoutput(cmd)
        if status:
            sys.stderr.write("There was an error : " + output)
            self.resulttc.AppendText("There was an error : " + output)
            sys.exit(1)
        self.resulttc.AppendText( output)
    
    def OnClear(self, event):
        self.resulttc.Clear()
        
    def OnExit(self, event):
        self.Destroy()

if __name__ == '__main__':
  
    app = wx.App()
    Example(None, title='Plagiarism Detection System')
    app.MainLoop()
