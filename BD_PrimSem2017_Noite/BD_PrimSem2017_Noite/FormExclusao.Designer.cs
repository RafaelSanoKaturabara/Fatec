namespace BD_PrimSem2017_Noite
{
    partial class FormExclusao
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
            this.groupBoxSaldo = new System.Windows.Forms.GroupBox();
            this.textBoxSaldo = new System.Windows.Forms.TextBox();
            this.groupBoxNome = new System.Windows.Forms.GroupBox();
            this.textBoxNome = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxCodigo = new System.Windows.Forms.TextBox();
            this.buttonExcluir = new System.Windows.Forms.Button();
            this.buttonRetornar = new System.Windows.Forms.Button();
            this.buttonVisualizar = new System.Windows.Forms.Button();
            this.groupBoxSaldo.SuspendLayout();
            this.groupBoxNome.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxSaldo
            // 
            this.groupBoxSaldo.BackColor = System.Drawing.Color.Cyan;
            this.groupBoxSaldo.Controls.Add(this.textBoxSaldo);
            this.groupBoxSaldo.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxSaldo.Location = new System.Drawing.Point(12, 184);
            this.groupBoxSaldo.Name = "groupBoxSaldo";
            this.groupBoxSaldo.Size = new System.Drawing.Size(200, 68);
            this.groupBoxSaldo.TabIndex = 14;
            this.groupBoxSaldo.TabStop = false;
            this.groupBoxSaldo.Text = "Saldo";
            this.groupBoxSaldo.Visible = false;
            // 
            // textBoxSaldo
            // 
            this.textBoxSaldo.Location = new System.Drawing.Point(25, 33);
            this.textBoxSaldo.Name = "textBoxSaldo";
            this.textBoxSaldo.Size = new System.Drawing.Size(148, 26);
            this.textBoxSaldo.TabIndex = 0;
            // 
            // groupBoxNome
            // 
            this.groupBoxNome.BackColor = System.Drawing.Color.Gold;
            this.groupBoxNome.Controls.Add(this.textBoxNome);
            this.groupBoxNome.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxNome.Location = new System.Drawing.Point(12, 99);
            this.groupBoxNome.Name = "groupBoxNome";
            this.groupBoxNome.Size = new System.Drawing.Size(451, 68);
            this.groupBoxNome.TabIndex = 13;
            this.groupBoxNome.TabStop = false;
            this.groupBoxNome.Text = "Nome";
            this.groupBoxNome.Visible = false;
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
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 68);
            this.groupBox1.TabIndex = 12;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Código";
            // 
            // textBoxCodigo
            // 
            this.textBoxCodigo.Location = new System.Drawing.Point(25, 33);
            this.textBoxCodigo.Name = "textBoxCodigo";
            this.textBoxCodigo.Size = new System.Drawing.Size(148, 26);
            this.textBoxCodigo.TabIndex = 0;
            // 
            // buttonExcluir
            // 
            this.buttonExcluir.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonExcluir.Location = new System.Drawing.Point(422, 373);
            this.buttonExcluir.Name = "buttonExcluir";
            this.buttonExcluir.Size = new System.Drawing.Size(146, 61);
            this.buttonExcluir.TabIndex = 11;
            this.buttonExcluir.Text = "Exluir";
            this.buttonExcluir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonExcluir.UseVisualStyleBackColor = true;
            this.buttonExcluir.Visible = false;
            this.buttonExcluir.Click += new System.EventHandler(this.buttonExcluir_Click);
            // 
            // buttonRetornar
            // 
            this.buttonRetornar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.buttonRetornar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRetornar.Image = global::BD_PrimSem2017_Noite.Properties.Resources.Botoes_5116_cross_48;
            this.buttonRetornar.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.buttonRetornar.Location = new System.Drawing.Point(219, 373);
            this.buttonRetornar.Name = "buttonRetornar";
            this.buttonRetornar.Size = new System.Drawing.Size(146, 61);
            this.buttonRetornar.TabIndex = 10;
            this.buttonRetornar.Text = "Retornar";
            this.buttonRetornar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.buttonRetornar.UseVisualStyleBackColor = false;
            this.buttonRetornar.Click += new System.EventHandler(this.buttonRetornar_Click);
            // 
            // buttonVisualizar
            // 
            this.buttonVisualizar.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonVisualizar.Location = new System.Drawing.Point(324, 12);
            this.buttonVisualizar.Name = "buttonVisualizar";
            this.buttonVisualizar.Size = new System.Drawing.Size(138, 59);
            this.buttonVisualizar.TabIndex = 15;
            this.buttonVisualizar.Text = "Visualizar";
            this.buttonVisualizar.UseVisualStyleBackColor = true;
            this.buttonVisualizar.Click += new System.EventHandler(this.buttonVisualizar_Click);
            // 
            // FormExclusao
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(581, 450);
            this.Controls.Add(this.buttonVisualizar);
            this.Controls.Add(this.groupBoxSaldo);
            this.Controls.Add(this.groupBoxNome);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonExcluir);
            this.Controls.Add(this.buttonRetornar);
            this.Name = "FormExclusao";
            this.Text = "FATEC-MC Exclusão";
            this.groupBoxSaldo.ResumeLayout(false);
            this.groupBoxSaldo.PerformLayout();
            this.groupBoxNome.ResumeLayout(false);
            this.groupBoxNome.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxSaldo;
        private System.Windows.Forms.TextBox textBoxSaldo;
        private System.Windows.Forms.GroupBox groupBoxNome;
        private System.Windows.Forms.TextBox textBoxNome;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxCodigo;
        private System.Windows.Forms.Button buttonExcluir;
        private System.Windows.Forms.Button buttonRetornar;
        private System.Windows.Forms.Button buttonVisualizar;
    }
}