using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace BD_PrimSem2017_Noite
{
    public partial class FormExclusao : Form
    {
        public FormExclusao()
        {
            InitializeComponent();
        }

        private void buttonRetornar_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// Botão excluir
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonExcluir_Click(object sender, EventArgs e)
        {
            DialogResult dlgResult =
                MessageBox.Show("Deseja excluir realmente?", "FATEC-MC Pergunta",
                MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (dlgResult == DialogResult.No)           // confirmou com sim?
            {
                textBoxCodigo.ReadOnly = false;                      // desabilita edição do código
                groupBoxNome.Visible = false;                        // torna visivel o nome
                groupBoxSaldo.Visible = false;                       // torna visivel o saldo
                buttonVisualizar.Visible = true;                     //
                buttonExcluir.Visible = false;                       // botão excluir desaparece
                textBoxCodigo.Text = string.Empty;                  // poderia ser usado null ou ""
                textBoxCodigo.Focus();
                return;                                  // continua no form
            }
            // disse sim

            try
            {
                FormBanco.cmd = FormBanco.conn.CreateCommand();
                FormBanco.cmd.CommandText = 
                    "DELETE from fatec_noite.clientes WHERE cod_cliente = " +
                    textBoxCodigo.Text + ";";
                FormBanco.cmd.Prepare();
                FormBanco.cmd.ExecuteNonQuery();
            }
            catch (MySqlException exv)
            {
                MessageBox.Show("Erro na exlucão!" + 
                exv.Message, "FATEC-MC Erro", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            textBoxCodigo.ReadOnly = false;                      // desabilita edição do código
            groupBoxNome.Visible = false;                        // torna visivel o nome
            groupBoxSaldo.Visible = false;                       // torna visivel o saldo
            buttonVisualizar.Visible = true;                     //
            buttonExcluir.Visible = false;                       // botão excluir desaparece                      
            textBoxCodigo.Text = string.Empty;                  // poderia ser usado null ou ""
            textBoxCodigo.Focus();
        }

        private void buttonVisualizar_Click(object sender, EventArgs e)
        {
            int nCodigo;                                        // para receber o código
            try
            {
                nCodigo = Convert.ToInt32(textBoxCodigo.Text);  // validar o código
            }
            catch (Exception)
            {
                MessageBox.Show("Digite um código válido!", "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxCodigo.Focus();
                return;
            }
            // tentar buscar a linha da tabela deste código
            try
            {
                FormBanco.cmd = FormBanco.conn.CreateCommand();     // criar comando
                FormBanco.cmd.CommandText =
                    "SELECT * from fatec_noite.clientes WHERE cod_cliente = " +
                    textBoxCodigo.Text + ";";
                FormBanco.cmd.Prepare();                            // prepara o comando
                FormBanco.cmd.ExecuteNonQuery();
            }
            catch (MySqlException exp)
            {
                MessageBox.Show("Cliente inexistente!" + Environment.NewLine +
                exp.Message, "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxCodigo.Focus();
                return;
            }
            // sucesso na seleção = agora ler a linha deste código
            FormBanco.dr = FormBanco.cmd.ExecuteReader();           // acessar o banco
            // verifidar se foi lido uma linha
            if (FormBanco.dr.Read())                                // tenho uma linha?
            {   // para uma linha apenas
                textBoxNome.Text =
                    FormBanco.dr.GetString("nome_cliente");         // pega o nome do cliente
                textBoxSaldo.Text =
                    Convert.ToString(FormBanco.dr.GetDecimal("saldo_cliente"));
                FormBanco.dr.Close();                               // fechar a leitura do banco
                textBoxCodigo.ReadOnly = true;                      // desabilita edição do código
                groupBoxNome.Visible = true;                        // torna visivel o nome
                groupBoxSaldo.Visible = true;                       // torna visivel o saldo
                buttonVisualizar.Visible = false;                   //
                buttonExcluir.Visible = true;                       // botão excluir aparece
            }
            else
            {   // não foi encontrada a linha
                MessageBox.Show("Código não encontrado!", "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                FormBanco.dr.Close();
                textBoxCodigo.Focus();
            }
        }
    }
}
