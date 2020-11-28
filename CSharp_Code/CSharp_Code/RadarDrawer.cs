using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace CSharp_Code
{
    public class RadarDrawer
    {
        private readonly PictureBox _field;
        private readonly Brush _PointColor = Brushes.Red;
        private const int POINT_RADIUS = 4;

        public RadarDrawer(PictureBox field)
        {
            _field = field;
            _field.Resize += _field_Resize;
        }

        private void _field_Resize(object sender, EventArgs e)
        {
            var g = _field.CreateGraphics();
            g.Clear(Color.White);
        }

        public void RedrawRadar(double distance, double angle)
        {
            var g = _field.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            DrawRadarContur(g);
            DrawRadarAngles(g);
            DrawPoint(g, distance, angle);            
        }

        public void TestRedrawRadar(List<string> data)
        {
            var g = _field.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            DrawRadarContur(g);
            DrawRadarAngles(g);

            for (int i = 0; i < data.Count; i++)
            {
                string[] splitResult = data[i].Split(';');
                double distance = double.Parse(splitResult[0]);
                double angle = double.Parse(splitResult[1]);
                int x = (int)(Math.Cos(angle * Math.PI / 180) * distance);
                int y = (int)(Math.Sin(angle * Math.PI / 180) * distance);

                g.FillEllipse(_PointColor, _field.Size.Width / 2 + x - POINT_RADIUS, _field.Size.Height - y - POINT_RADIUS,
                    2 * POINT_RADIUS, 2 * POINT_RADIUS);
            }
        }

        private void DrawRadarContur(Graphics g)
        {
            int width = _field.Size.Width;
            int height = _field.Size.Height;
            
            //Big
            g.DrawEllipse(new Pen(Color.DarkGreen, 3), 0, 0, width, 2 * height);

            //Medium            
            g.DrawEllipse(new Pen(Color.DarkOrange, 3), width / 6, (height / 3), ((2 * width) / 3), (4 * height) / 3);

            //Low
            int firstResult = width / 3;
            int secondResult = (2 * height) / 3;
            g.DrawEllipse(new Pen(Color.DarkRed, 3), firstResult, secondResult, firstResult, secondResult);
        }

        //TODO: ограничить прямые окружностями
        private void DrawRadarAngles(Graphics g)
        {
            var pen = new Pen(Color.Black, 2);
            var radarCenter = new Point(_field.Width / 2, _field.Height);

            g.DrawLine(pen, radarCenter, new Point(0,0));
            g.DrawLine(pen, radarCenter, new Point(_field.Width / 2, 0));
            g.DrawLine(pen, radarCenter, new Point(_field.Size.Width, 0));
        }

        private void DrawPoint(Graphics g, double distance, double angle)
        {
            int x = (int)(Math.Cos(angle * Math.PI / 180) * distance);
            int y = (int)(Math.Sin(angle * Math.PI / 180) * distance);

            g.FillEllipse(_PointColor,
                _field.Width / 2 + x - POINT_RADIUS, _field.Height - y - POINT_RADIUS,
                2 * POINT_RADIUS, 2 * POINT_RADIUS);
        }
    }
}
