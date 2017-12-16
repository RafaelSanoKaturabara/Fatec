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
    public partial class FormIncluir : Form
    {
        /// <summary>
        /// Construtor
        /// </summary>
        public FormIncluir()
        {
            InitializeComponent();
            textBoxCodigo.Focus();
        }

        /// <summary>
        /// Quando o mouse estiver sobre o botão Retornar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_MouseEnter(object sender, EventArgs e)
        {
            buttonRetornar.FlatStyle = FlatStyle.Flat;
        }

        /// <summary>
        /// Quando o mouse sair do botão Retornar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_MouseLeave(object sender, EventArgs e)
        {
            buttonRetornar.FlatStyle = FlatStyle.Standard;
        }

        /// <summary>
        /// Botão retornar foi clicado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Quando for acionado o botão incluir
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonIncluir_Click(object sender, EventArgs e)
        {
            int nCodCliente;                // recebe o código do cliente
            string szNomeCliente,           // recebe o nome do cliente
                szFormatacao;               // para formatar o saldo
            decimal dcSaldoCliente;         // recebe o saldo do cliente
            // codigo do cliente
            try
            {
                nCodCliente = Convert.ToInt32(textBoxCodigo.Text);
            }
            catch (Exception)
            {
                MessageBox.Show("Digite um código válido!", "FATEC-MC Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxCodigo.Focus();
                return;                                 // continua no form
            }
            // nome
            szNomeCliente = textBoxNome.Text;
            if (szNomeCliente.Length < 5)                // testa extensão do nome
            {
                MessageBox.Show("Digite um nome válido!", "FATEC-MC Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxNome.Focus();
                return;
            }
            // saldo
            try
            {
                //if (textBoxSaldo.Text.Contains("."))
                //    textBoxSaldo.Text = textBoxSaldo.Text.Replace(".", ",");
                dcSaldoCliente = Convert.ToDecimal(textBoxSaldo.Text);
                //szFormatacao = Convert.ToString(dcSaldoCliente);
                if (textBoxSaldo.Text.Contains(","))
                    textBoxSaldo.Text = textBoxSaldo.Text.Replace(",", ".");
            }
            catch (Exception)
            {
                MessageBox.Show("Digite um saldo válido!", "FATEC-MC Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxSaldo.Focus();
                return;
            }
            // fazer a inserção no banco
            try
            {
                FormBanco.cmd = FormBanco.conn.CreateCommand();
                FormBanco.cmd.CommandText =
                "INSERT INTO fatec_noite.clientes (cod_cliente, nome_cliente, saldo_cliente)" +
                    "VALUES (" + nCodCliente + ", \'" + szNomeCliente + "\', " +
                    textBoxSaldo.Text + ");";
                FormBanco.cmd.Prepare();
                FormBanco.cmd.ExecuteNonQuery();
                textBoxCodigo.Text = string.Empty;
                textBoxNome.Text = string.Empty;
                textBoxSaldo.Text = string.Empty;
                textBoxCodigo.Focus();
            }
            catch (MySqlException exc)
            {
                MessageBox.Show("Erro na Inserção!" + Environment.NewLine +
                exc.Message, "FATEC-MC Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
