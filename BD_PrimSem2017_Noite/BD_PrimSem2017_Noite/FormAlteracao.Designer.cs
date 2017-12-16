namespace BD_PrimSem2017_Noite
{
    partial class FormAlteracao
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
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxSaldo = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBoxNome = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxCodigo = new System.Windows.Forms.TextBox();
            this.buttonAlterar = new System.Windows.Forms.Button();
            this.buttonRetornar = new System.Windows.Forms.Button();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Cyan;
            this.groupBox3.Controls.Add(this.textBoxSaldo);
            this.groupBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox3.Location = new System.Drawing.Point(56, 202);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(200, 68);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Saldo";
            // 
            // textBoxSaldo
            // 
            this.textBoxSaldo.Location = new System.Drawing.Point(25, 33);
            this.textBoxSaldo.Name = "textBoxSaldo";
            this.textBoxSaldo.Size = new System.Drawing.Size(148, 26);
            this.textBoxSaldo.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Gold;
            this.groupBox2.Controls.Add(this.textBoxNome);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(56, 117);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(451, 68);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Nome";
            // 
            // textBoxNome
            // 
            this.textBoxNome.Location = new System.Drawing.Point(25, 33);
            this.textBoxNome.MaxLength = 40;
            this.textBoxNome.Name = "textBoxNome";
            this.textBoxNome.Size = new System.Drawing.Size(420, 26);
            this.textBoxNome.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Cyan;
            this.groupBox1.Controls.Add(this.textBoxCodigo);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(56, 30);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 68);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Código";
            // 
            // textBoxCodigo
            // 
            this.textBoxCodigo.Location = new System.Drawing.Point(25, 33);
            this.textBoxCodigo.Name = "textBoxCodigo";
            this.textBoxCodigo.Size = new System.Drawing.Size(148, 26);
            this.textBoxCodigo.TabIndex = 0;
            this.textBoxCodigo.Leave += new System.EventHandler(this.textBoxCodigo_Leave);
            // 
            // buttonAlterar
            // 
            this.buttonAlterar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonAlterar.Location = new System.Drawing.Point(466, 391);
            this.buttonAlterar.Name = "buttonAlterar";
            this.buttonAlterar.Size = new System.Drawing.Size(146, 61);
            this.buttonAlterar.TabIndex = 6;
            this.buttonAlterar.Text = "Alterar";
            this.buttonAlterar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonAlterar.UseVisualStyleBackColor = true;
            this.buttonAlterar.Click += new System.EventHandler(this.buttonAlterar_Click);
            // 
            // buttonRetornar
            // 
            this.buttonRetornar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.buttonRetornar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRetornar.Image = global::BD_PrimSem2017_Noite.Properties.Resources.Botoes_5116_cross_48;
            this.buttonRetornar.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.buttonRetornar.Location = new System.Drawing.Point(263, 391);
            this.buttonRetornar.Name = "buttonRetornar";
            this.buttonRetornar.Size = new System.Drawing.Size(146, 61);
            this.buttonRetornar.TabIndex = 5;
            this.buttonRetornar.Text = "Retornar";
            this.buttonRetornar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonRetornar.UseVisualStyleBackColor = false;
            this.buttonRetornar.Click += new System.EventHandler(this.buttonRetornar_Click);
            this.buttonRetornar.MouseEnter += new System.EventHandler(this.buttonRetornar_MouseEnter);
            this.buttonRetornar.MouseLeave += new System.EventHandler(this.buttonRetornar_MouseLeave);
            // 
            // FormAlteracao
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(697, 467);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonAlterar);
            this.Controls.Add(this.buttonRetornar);
            this.Name = "FormAlteracao";
            this.Text = "FATEC-MC Alteração de Clientes";
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxSaldo;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBoxNome;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxCodigo;
        private System.Windows.Forms.Button buttonAlterar;
        private System.Windows.Forms.Button buttonRetornar;
    }
}