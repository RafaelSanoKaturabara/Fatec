namespace BD_PrimSem2017_Noite
{
    partial class FormIncluir
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonRetornar = new System.Windows.Forms.Button();
            this.buttonIncluir = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxCodigo = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBoxNome = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxSaldo = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonRetornar
            // 
            this.buttonRetornar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.buttonRetornar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRetornar.Image = global::BD_PrimSem2017_Noite.Properties.Resources.Botoes_5116_cross_48;
            this.buttonRetornar.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.buttonRetornar.Location = new System.Drawing.Point(221, 382);
            this.buttonRetornar.Name = "buttonRetornar";
            this.buttonRetornar.Size = new System.Drawing.Size(146, 61);
            this.buttonRetornar.TabIndex = 0;
            this.buttonRetornar.Text = "Retornar";
            this.buttonRetornar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonRetornar.UseVisualStyleBackColor = false;
            this.buttonRetornar.Click += new System.EventHandler(this.buttonRetornar_Click);
            this.buttonRetornar.MouseEnter += new System.EventHandler(this.buttonRetornar_MouseEnter);
            this.buttonRetornar.MouseLeave += new System.EventHandler(this.buttonRetornar_MouseLeave);
            // 
            // buttonIncluir
            // 
            this.buttonIncluir.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonIncluir.Location = new System.Drawing.Point(424, 382);
            this.buttonIncluir.Name = "buttonIncluir";
            this.buttonIncluir.Size = new System.Drawing.Size(146, 61);
            this.buttonIncluir.TabIndex = 1;
            this.buttonIncluir.Text = "Incluir";
            this.buttonIncluir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonIncluir.UseVisualStyleBackColor = true;
            this.buttonIncluir.Click += new System.EventHandler(this.buttonIncluir_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Cyan;
            this.groupBox1.Controls.Add(this.textBoxCodigo);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(14, 21);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 68);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Código";
            // 
            // textBoxCodigo
            // 
            this.textBoxCodigo.Location = new System.Drawing.Point(6, 25);
            this.textBoxCodigo.Name = "textBoxCodigo";
            this.textBoxCodigo.Size = new System.Drawing.Size(148, 26);
            this.textBoxCodigo.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Gold;
            this.groupBox2.Controls.Add(this.textBoxNome);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(14, 108);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(451, 68);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Nome";
            // 
            // textBoxNome
            // 
            this.textBoxNome.Location = new System.Drawing.Point(6, 25);
            this.textBoxNome.MaxLength = 40;
            this.textBoxNome.Name = "textBoxNome";
            this.textBoxNome.Size = new System.Drawing.Size(420, 26);
            this.textBoxNome.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Cyan;
            this.groupBox3.Controls.Add(this.textBoxSaldo);
            this.groupBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox3.Location = new System.Drawing.Point(14, 193);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 68);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Saldo";
            // 
            // textBoxSaldo
            // 
            this.textBoxSaldo.Location = new System.Drawing.Point(6, 25);
            this.textBoxSaldo.Name = "textBoxSaldo";
            this.textBoxSaldo.Size = new System.Drawing.Size(148, 26);
            this.textBoxSaldo.TabIndex = 0;
            // 
            // FormIncluir
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(582, 484);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonIncluir);
            this.Controls.Add(this.buttonRetornar);
            this.Name = "FormIncluir";
            this.Text = "FATEC-MC = Inclusão no Banco";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonRetornar;
        private System.Windows.Forms.Button buttonIncluir;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxCodigo;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBoxNome;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxSaldo;
    }
}