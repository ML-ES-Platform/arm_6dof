import json
import wx
from graphviz import Digraph

# with open("c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo.json", "r") as read_file:
#     data = json.load(read_file)

# print (data)

# print ("Done")

#https://www.techiediaries.com/python-gui-wxpython-tutorial-urllib-json/


def DotGen(jsonFile, dotFile):
    dot = Digraph(comment='arm 6-dof demo')

    with open(jsonFile, "r") as read_file:
        JSON_object = json.load(read_file)
        applicationName = JSON_object["Name"]
        linkComps = JSON_object["Components"]
        for comp in linkComps:

            componentName = linkComps[comp]
            if "Name" in linkComps[comp]:
                componentName = linkComps[comp]["Name"]
            
            if (componentName != "null"):

                # Components Groups
                if "Groups" in linkComps[comp]:
                    linkGroup = linkComps[comp]["Groups"]
                    for grp in linkGroup:
                        groupName = str(linkGroup[grp])

                        # Name
                        if "Name" in linkGroup[grp]:
                            groupName = linkGroup[grp]["Name"]

                        # Channels
                        if "Channels" in linkGroup[grp]:
                            linkChannels = linkGroup[grp]["Channels"]
                            for el in linkChannels:
                                # NOTE: the subgraph name needs to begin with 'cluster' (all lowercase)
                                #       so that Graphviz recognizes it as a special cluster subgraph
                                with dot.subgraph(name="cluster_"+linkComps[comp]["Name"]) as c:
                                    c.attr(color='blue')
                                    c.node_attr['style'] = 'filled'
                                    c.attr(label=linkComps[comp]["Name"])
                                    c.node(el)
                                print (el)
                                dot.edge( el, str(linkChannels[el]))

    # with open(jsonFile, "r") as read_file:
    #     JSON_object = json.load(read_file)

    #     linkComps = JSON_object["Components"]
    #     for comp in linkComps:

    #         linkGroup = linkComps[comp]["Groups"]["Channels"]
    #         for el in linkGroup:
    #             # NOTE: the subgraph name needs to begin with 'cluster' (all lowercase)
    #             #       so that Graphviz recognizes it as a special cluster subgraph
    #             with dot.subgraph(name="cluster_"+linkComps[comp]["Component"]) as c:
    #                 c.attr(color='blue')
    #                 c.node_attr['style'] = 'filled'
    #                 c.attr(label=linkComps[comp]["Name"])
    #                 c.node(el)

    #             dot.edge( el, linkGroup[el])

    dot.render('test-output/round-table.gv', view=True)
    print(dot.source)

    # g = Digraph('G', filename='cluster.gv')
    # g.view()


def CfgHeadGen(jsonFile, headerFile):
        
    f_head = open(headerFile, "w")
    f_head.write("/**\n")
    f_head.write(" * @file arm_6dof_demo_config.h\n")
    f_head.write(" * @author your name (you@domain.com)\n")
    f_head.write(" * @brief \n")
    f_head.write(" * @version 0.1\n")
    f_head.write(" * @date 2020-06-12\n")
    f_head.write(" * \n")
    f_head.write(" * @copyright Copyright (c) 2020\n")
    f_head.write(" * \n")
    f_head.write(" */\n")

    f_head.write("#ifndef _ARM_6DOF_DEMO_CONFIG_H_\n")
    f_head.write("#define _ARM_6DOF_DEMO_CONFIG_H_\n")
    f_head.write("\n")
    f_head.write("#include \"platform_config.h\"\n")
    f_head.write("\n")

    with open(jsonFile, "r") as read_file:
        JSON_object = json.load(read_file)
        applicationName = JSON_object["Name"]
        linkComps = JSON_object["Components"]
        for comp in linkComps:

            componentName = linkComps[comp]
            if "Name" in linkComps[comp]:
                componentName = linkComps[comp]["Name"]
            
            if (componentName != "null"):
                f_head.write("#define "+ componentName.upper()+"_CONFIG"+"\n")

                # Components Groups
                if "Groups" in linkComps[comp]:
                    linkGroup = linkComps[comp]["Groups"]
                    for grp in linkGroup:
                        groupName = str(linkGroup[grp])

                        # Name
                        if "Name" in linkGroup[grp]:
                            groupName = linkGroup[grp]["Name"]

                        # Channels
                        if "Channels" in linkGroup[grp]:
                            f_head.write("enum "+ groupName.upper()+"_IdType {")
                            linkChannels = linkGroup[grp]["Channels"]
                            for el in linkChannels:
                                f_head.write(el + ", ")
                            f_head.write(groupName.upper() +"_CHANNEL_NR_OF};\n")
                        
                        # Defines
                        if "Defines" in linkGroup[grp]:
                            linkDefines = linkGroup[grp]["Defines"]
                            for el in linkDefines:
                                f_head.write("#define "+el + " " + str(linkDefines[el])+ "\n")
                        
                # Components Paths in project
                if "Path" in linkComps[comp]:
                    linkPath = linkComps[comp]["Path"]
                    f_head.write("#include \""+ str(linkPath) + str(componentName)+ ".h\"\n")

                f_head.write("\n")

    f_head.write("Std_ReturnType " + applicationName + "_config(void);\n")

    f_head.write("\n")
    f_head.write("#endif // _ARM_6DOF_DEMO_CONFIG_H_\n")
    f_head.close()


def CfgSrcGen(jsonFile, srcFile):
        
    with open(jsonFile, "r") as read_file:
        JSON_object = json.load(read_file)
        applicationName = JSON_object["Name"]
        appDescription = JSON_object["Description"]

        f_src = open(srcFile, "w")
        f_src.write("\
/**\n\
* @file arm_6dof_demo_config_gen.cpp\n\
* @author your name (you@domain.com)\n\
* @brief \n\
* @version 0.1\n\
* @date 2020-06-12\n\
* \n\
* @copyright Copyright (c) 2020\n\
* \n\
*/\n\
\n\
#include \"" + applicationName + "_cfg_gen.h\"\n\
\n\
Std_ReturnType " + applicationName + "_config(void)\n\
{\n\
    Serial.begin(115200);\n\
    Serial.println(\""+appDescription+"\");\n\
    Std_ReturnType error = E_OK;\n")


        linkComps = JSON_object["Components"]
        for comp in linkComps:

            componentName = linkComps[comp]
            if "Name" in linkComps[comp]:
                componentName = linkComps[comp]["Name"]
            
            if (componentName != "null"):
                # Components Groups
                if "Groups" in linkComps[comp]:
                    linkGroup = linkComps[comp]["Groups"]
                    for grp in linkGroup:
                        groupName = str(linkGroup[grp])

                        # Name
                        if "Name" in linkGroup[grp]:
                            groupName = linkGroup[grp]["Name"]
                        # Parent 
                        parentChannelStr = ""
                        if "Parent" in linkGroup[grp]:
                            parentChannelStr = linkGroup[grp]["Parent"] + ", "

                        # Channels
                        if "Channels" in linkGroup[grp]:
                            
                            f_src.write("\n")
                            linkChannels = linkGroup[grp]["Channels"]

                            for el in linkChannels:
                                if (linkChannels[el]!= "null"):
                                    f_src.write("\
    error += "+ componentName.upper() +"_ChannelSetup(" + parentChannelStr + el +", "+linkChannels[el]+");\n")
                            # Pull
                            if "Pull" in linkGroup[grp]:
                                
                                f_src.write("\n")
                                linkChannels = linkGroup[grp]["Channels"]

                                for el in linkChannels:
                                    if (linkChannels[el]!= "null"):
                                        f_src.write("\
    error += "+ componentName.upper() +"_SetPullMethod(" + parentChannelStr + el +", "+linkGroup[grp]["Pull"]+");\n")

                            # Push
                            if "Push" in linkGroup[grp]:
                                
                                f_src.write("\n")
                                linkChannels = linkGroup[grp]["Channels"]

                                for el in linkChannels:
                                    if (linkChannels[el]!= "null"):
                                        f_src.write("\
    error += "+ componentName.upper() +"_SetPushMethod(" +parentChannelStr+ el +", "+linkGroup[grp]["Push"]+");\n")


                            f_src.write("\
    Serial.print(\"" + groupName.upper() + " configured - Error : \");\n\
    Serial.println(error);\n")
                               

                f_src.write("\n")

    f_src.write("    return error;\n")
    f_src.write("}\n")
    f_src.close()





class NewsPanel(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
        self.SetBackgroundColour("gray")

        self.sources_list = wx.ListCtrl(
            self, 
            style=wx.LC_REPORT | wx.BORDER_SUNKEN
        )
        self.sources_list.InsertColumn(0, "Component Group", width=200)
        
        self.news_list = wx.ListCtrl(
            self, 
            size = (-1 , - 1),
            style=wx.LC_REPORT | wx.BORDER_SUNKEN
        )
        self.news_list.InsertColumn(0, 'Upper Channel')
        self.news_list.InsertColumn(1, 'Lower Channel')
        
        
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(self.sources_list, 0, wx.ALL | wx.EXPAND)
        sizer.Add(self.news_list, 1, wx.ALL | wx.EXPAND)
        
        self.SetSizer(sizer)
        self.getNewsSources()
        self.sources_list.Bind(wx.EVT_LIST_ITEM_SELECTED, self.OnSourceSelected)
        self.news_list.Bind(wx.EVT_LIST_ITEM_SELECTED , self.OnLinkSelected)
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
    
    def OnPaint(self, evt):
        width, height = self.news_list.GetSize()
        for i in range(2):
            self.news_list.SetColumnWidth(i, width/2)
        evt.Skip()
    
    def OnSourceSelected(self, event):
         source = event.GetText().replace(" ", "-")
        #  print(source)
         self.getNews(source)
    
    
    def OnLinkSelected(self, event):
          print(event.GetText()) 
          webbrowser.open(event.GetText())           

                   
    def getNews(self, source):
        with open("c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo.json", "r") as read_file:
            JSON_object = json.load(read_file)
        
        # print(source)
        self.news_list.DeleteAllItems()
        linkGroup = JSON_object["Components"][source]["Groups"]
        for grp in linkGroup:
            linkCnl = JSON_object["Components"][source]["Groups"][grp]["Channels"]
            
            for cnl in linkCnl:

                print (cnl)
                print (linkCnl[cnl])
                index = 0
                self.news_list.InsertItem(index, cnl)
                self.news_list.SetItem(index, 1, linkCnl[cnl])
                index += 1


    def getNewsSources(self):
        with open("c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo.json", "r") as read_file:
            JSON_object = json.load(read_file)
          
            # print( JSON_object["Components"] )
            for el in JSON_object["Components"]:
                print (el)
                self.sources_list.InsertItem(0, el)



class MainWindow(wx.Frame):
    def __init__(self, parent, title):

        super(MainWindow, self).__init__(parent, title = title, size = (600,500))
        self.Centre()

        NewsPanel(self)
        #self.panel.SetBackgroundColour("gray")
        self.createStatusBar()
        self.createMenu()
        
    def createStatusBar(self):
        self.CreateStatusBar() #A Statusbar at the bottom of the window


    def createMenu(self):
    
        menu= wx.Menu()
        menuExit = menu.Append(wx.ID_EXIT, "E&xit", "Quit application")
        menuDot = menu.Append(wx.ID_ANY, "&Dot Generate", "Generate dot file for dependencies")
              
        menuBar = wx.MenuBar()
        menuBar.Append(menu,"&File")

        genMenu = wx.Menu()
        menuCfg = genMenu.Append(wx.ID_ANY, "&Config Generate", "Generate Configuration file for dependencies")
        
        menuBar.Append(genMenu,"&Generate")

        self.SetMenuBar(menuBar)

        self.Bind(wx.EVT_MENU, self.OnExit, menuExit)
        self.Bind(wx.EVT_MENU, self.OnDotGen, menuDot)
        self.Bind(wx.EVT_MENU, self.OnCfgGen, menuCfg)

        # self.Bind(wx.EVT_MENU, self.OnCfgGen, genMenu)

    def OnExit(self, event):
        self.Close(True) 

    def OnDotGen(self, event):
        jsonFile = "c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo.json"
        dotFile = "c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo_cfg_gen.dot"
        DotGen(jsonFile, dotFile)


    def OnCfgGen(self, event):
        jsonFile = "c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo.json"
        headerFile = "c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo_cfg_gen.h"
        srcFile = "c:/MicroLabOS_WS/ES_Platform/src/ASW/arm_6dof/demo/arm_6dof_demo_cfg_gen.cpp"
        CfgHeadGen(jsonFile, headerFile)
        CfgSrcGen(jsonFile, srcFile)

        
        

        

        

if __name__ == '__main__':
    app = wx.App()
    window= MainWindow(None, "Newsy - read worldwide news!")
    window.Show()
    app.MainLoop()