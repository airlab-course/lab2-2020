namespace CSharp_Code
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.GenerateData_Button = new System.Windows.Forms.Button();
            this.GenerateData_Timer = new System.Windows.Forms.Timer(this.components);
            this.RadarField_PictureBox = new System.Windows.Forms.PictureBox();
            this.Radar_Panel = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.RadarField_PictureBox)).BeginInit();
            this.Radar_Panel.SuspendLayout();
            this.SuspendLayout();
            // 
            // GenerateData_Button
            // 
            this.GenerateData_Button.Location = new System.Drawing.Point(12, 12);
            this.GenerateData_Button.Name = "GenerateData_Button";
            this.GenerateData_Button.Size = new System.Drawing.Size(124, 53);
            this.GenerateData_Button.TabIndex = 1;
            this.GenerateData_Button.Text = "Сгенерировать данные";
            this.GenerateData_Button.UseVisualStyleBackColor = true;
            this.GenerateData_Button.Click += new System.EventHandler(this.GenerateData_Button_Click);
            // 
            // GenerateData_Timer
            // 
            this.GenerateData_Timer.Interval = 250;
            this.GenerateData_Timer.Tick += new System.EventHandler(this.GenerateData_Timer_Tick);
            // 
            // RadarField_PictureBox
            // 
            this.RadarField_PictureBox.BackColor = System.Drawing.Color.White;
            this.RadarField_PictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RadarField_PictureBox.Location = new System.Drawing.Point(0, 0);
            this.RadarField_PictureBox.Name = "RadarField_PictureBox";
            this.RadarField_PictureBox.Size = new System.Drawing.Size(598, 311);
            this.RadarField_PictureBox.TabIndex = 0;
            this.RadarField_PictureBox.TabStop = false;
            // 
            // Radar_Panel
            // 
            this.Radar_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Radar_Panel.BackColor = System.Drawing.SystemColors.Info;
            this.Radar_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Radar_Panel.Controls.Add(this.RadarField_PictureBox);
            this.Radar_Panel.Location = new System.Drawing.Point(12, 116);
            this.Radar_Panel.Name = "Radar_Panel";
            this.Radar_Panel.Size = new System.Drawing.Size(600, 313);
            this.Radar_Panel.TabIndex = 0;
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(624, 441);
            this.Controls.Add(this.GenerateData_Button);
            this.Controls.Add(this.Radar_Panel);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.RadarField_PictureBox)).EndInit();
            this.Radar_Panel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button GenerateData_Button;
        private System.Windows.Forms.Timer GenerateData_Timer;
        private System.Windows.Forms.PictureBox RadarField_PictureBox;
        private System.Windows.Forms.Panel Radar_Panel;
    }
}

