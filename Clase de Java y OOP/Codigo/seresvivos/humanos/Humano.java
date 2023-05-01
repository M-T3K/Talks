package seresvivos.humanos;

import seresvivos.especiales.AnimalCompania;

public class Humano extends AnimalCompania {
	
	private String apellidos;
	private String nacimiento;
	private String ocupacion;
	private int    inteligencia;
		
	public Humano(String especie, int edad, double peso, double tamano, boolean cola, boolean pulmones,
			boolean espina_dorsal, boolean glandulas_mamarias, boolean cuerpo_peludo, boolean sexo, String nombre,
			String direccion, String apellidos, String nacimiento, String ocupacion, int inteligencia) {
		
		super(especie, edad, peso, tamano, cola, pulmones, espina_dorsal, glandulas_mamarias, cuerpo_peludo, sexo, nombre,
				direccion);
		
		this.apellidos = apellidos;
		this.nacimiento	= nacimiento;
		this.ocupacion = ocupacion;
		this.inteligencia = inteligencia;
		
	}
	
	public String getApellidos() {
		
		return this.apellidos;
		
	}
	
	public String getNacimiento() {
		
		return this.nacimiento;
		
	}
	
	public String getOcupacion() {
		
		return this.ocupacion;
		
	}
	
	public int getInteligencia() {
		
		return this.inteligencia;
		
	}
	

	public void setApellidos(String apellidos) {
		
		this.apellidos = apellidos;
		
	}
	
	public void setNacimiento(String nacimiento) {
		
		this.nacimiento = nacimiento;
		
	}
	
	public void setOcupacion(String ocupacion) {
		
		this.ocupacion = ocupacion;
		
	}
	
	public void setInteligencia(int inteligencia) {
		
		this.inteligencia = inteligencia;
		
	}
	
	@Override
	public boolean equals(Object Obj) {
		
		if(Obj instanceof Humano) {
			
			Humano h = (Humano)(Obj);
			return super.equals(h)
					&& (this.apellidos.equals(h.getApellidos()))
					&& (this.nacimiento.equals(h.getNacimiento()))
					&& (this.ocupacion.equals(h.getOcupacion()))
					&& (this.inteligencia == h.getInteligencia());
			
		}
		else {
			
			return false;
			
		}
		
	}
	
	@Override
	public String toString() {
		
		String sex_str = this.getSexo() ? "femenino" : "masculino";
		
		return "Esta persona se llama " + this.getNombre() + " " + this.apellidos + 
				". Nació en " + this.nacimiento + " y ahora vive en " + this.getDireccion()
				+ ". Su sexo es " + sex_str + " y se dedica a ser " +
				this.ocupacion + ". Tiene un CI de " + this.inteligencia + ".";
		
	}
}
