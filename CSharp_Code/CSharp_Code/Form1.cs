using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Windows.Forms;

namespace CSharp_Code
{
    public partial class Form1 : Form
    {
        private RadarDrawer _radarDrawer;
        private SerialPort _serialReader;
        private DataGenerator _dataGenerator;

        private List<string> _dataList;

        public Form1()
        {
            InitializeComponent();
            InitFields();
        }

        private void InitFields()
        {
            _radarDrawer = new RadarDrawer(RadarField_PictureBox);
            _dataGenerator = new DataGenerator();
            _serialReader = new SerialPort();
            _serialReader.BaudRate = 115200;
            _serialReader.DataReceived += _serialReader_DataReceived;
        }

        private void _serialReader_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string line = _serialReader.ReadLine();
            string[] parseResult = line.Split();
            double dist = double.Parse(parseResult[0]);
            double angle = double.Parse(parseResult[1]);

           _radarDrawer.RedrawRadar(dist, angle);
        }

        private void GenerateData_Button_Click(object sender, EventArgs e)
        {
            GenerateData_Timer.Enabled = !GenerateData_Timer.Enabled;
        }

        private void GenerateData_Timer_Tick(object sender, EventArgs e)
        {
            _dataList = _dataGenerator.GenerateNewData();
            if (_dataList == null)
                return;
            else
                _radarDrawer.TestRedrawRadar(_dataList);
        }
    }
}
