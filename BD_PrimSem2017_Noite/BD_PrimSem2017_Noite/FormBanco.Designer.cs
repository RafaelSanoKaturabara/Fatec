namespace BD_PrimSem2017_Noite
{
    partial class FormBanco
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormBanco));
            this.toolStripAcoes = new System.Windows.Forms.ToolStrip();
            this.toolStripDropDownButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.inserirToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.excluirToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.alterarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listagemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sairDoProgramaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripAcoes.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStripAcoes
            // 
            this.toolStripAcoes.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold);
            this.toolStripAcoes.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripDropDownButton1});
            this.toolStripAcoes.Location = new System.Drawing.Point(0, 0);
            this.toolStripAcoes.Name = "toolStripAcoes";
            this.toolStripAcoes.Size = new System.Drawing.Size(572, 28);
            this.toolStripAcoes.TabIndex = 0;
            this.toolStripAcoes.Text = "Ações no Banco";
            // 
            // toolStripDropDownButton1
            // 
            this.toolStripDropDownButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.inserirToolStripMenuItem,
            this.excluirToolStripMenuItem,
            this.alterarToolStripMenuItem,
            this.toolStripSeparator1,
            this.listagemToolStripMenuItem,
            this.toolStripSeparator2,
            this.sairDoProgramaToolStripMenuItem});
            this.toolStripDropDownButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripDropDownButton1.Image")));
            this.toolStripDropDownButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripDropDownButton1.Name = "toolStripDropDownButton1";
            this.toolStripDropDownButton1.Size = new System.Drawing.Size(159, 25);
            this.toolStripDropDownButton1.Text = "Ações no Banco";
            // 
            // inserirToolStripMenuItem
            // 
            this.inserirToolStripMenuItem.ForeColor = System.Drawing.Color.LightSeaGreen;
            this.inserirToolStripMenuItem.Name = "inserirToolStripMenuItem";
            this.inserirToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.inserirToolStripMenuItem.Text = "Inserir";
            this.inserirToolStripMenuItem.Click += new System.EventHandler(this.inserirToolStripMenuItem_Click);
            // 
            // excluirToolStripMenuItem
            // 
            this.excluirToolStripMenuItem.ForeColor = System.Drawing.Color.Red;
            this.excluirToolStripMenuItem.Name = "excluirToolStripMenuItem";
            this.excluirToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.excluirToolStripMenuItem.Text = "Excluir";
            this.excluirToolStripMenuItem.Click += new System.EventHandler(this.excluirToolStripMenuItem_Click);
            // 
            // alterarToolStripMenuItem
            // 
            this.alterarToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.alterarToolStripMenuItem.Name = "alterarToolStripMenuItem";
            this.alterarToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.alterarToolStripMenuItem.Text = "Alterar";
            this.alterarToolStripMenuItem.Click += new System.EventHandler(this.alterarToolStripMenuItem_Click);
            // 
            // listagemToolStripMenuItem
            // 
            this.listagemToolStripMenuItem.Name = "listagemToolStripMenuItem";
            this.listagemToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.listagemToolStripMenuItem.Text = "Listagem";
            this.listagemToolStripMenuItem.Click += new System.EventHandler(this.listagemToolStripMenuItem_Click);
            // 
            // sairDoProgramaToolStripMenuItem
            // 
            this.sairDoProgramaToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.sairDoProgramaToolStripMenuItem.Name = "sairDoProgramaToolStripMenuItem";
            this.sairDoProgramaToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.sairDoProgramaToolStripMenuItem.Text = "Sair do Programa";
            this.sairDoProgramaToolStripMenuItem.Click += new System.EventHandler(this.sairDoProgramaToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(209, 6);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(209, 6);
            // 
            // FormBanco
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572, 453);
            this.Controls.Add(this.toolStripAcoes);
            this.Name = "FormBanco";
            this.Text = "FATEC-MC - Teste Banco de Dados";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormBanco_FormClosing);
            this.toolStripAcoes.ResumeLayout(false);
            this.toolStripAcoes.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStripAcoes;
        private System.Windows.Forms.ToolStripDropDownButton toolStripDropDownButton1;
        private System.Windows.Forms.ToolStripMenuItem inserirToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem excluirToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem alterarToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem listagemToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem sairDoProgramaToolStripMenuItem;
    }
}

