package com.onetwofivegames.kungfoobarracuda.exceptions;

public class ResourceNotFound extends DescentExceptionBase {
	public ResourceNotFound(String resourceName) {
		m_resourceName = resourceName;
	}

	@Override
	public String toString() {
		return "ResourceNotFound: " + m_resourceName + "\n" + super.toString();
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String m_resourceName;
}
