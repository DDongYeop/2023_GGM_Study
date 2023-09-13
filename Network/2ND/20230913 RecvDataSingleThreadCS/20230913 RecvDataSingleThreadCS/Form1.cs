using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;

namespace _20230913_RecvDataSingleThreadCS
{
    public partial class Form1 : Form
    {
        Thread recvThread = null;
        bool runFlags = true;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            recvThread = new Thread(RecvData);
            recvThread.Start();
        }

        private void RecvData()
        {
            while (runFlags)
            {
                Thread.Sleep(1);
                foreach (var proc in Process.GetProcesses())
                {
                    if (proc.ProcessName.ToString() == "SendDataCS")
                    {
                        runFlags = false;
                        label2.Text = "전달된 값은 " + SendDataCS.Form1.SendName;
                    }
                }
            }
            recvThread.Abort();
        }
    }
}
