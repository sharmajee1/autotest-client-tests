/*
 * (C) Copyright IBM Corp. 2004, 2005
 * Copyright (c) 2005, Intel Corporation
 * Copyright (c) 2005, University of New Hampshire
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Author(s):
 *      Carl McAdams <carlmc@us.ibm.com>
 *      Xiaowei Yang <xiaowei.yang@intel.com>
 *      Qun Li <qun.li@intel.com>
 *      Donald A. Barre <dbarre@unh.edu>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiUnsubscribe
 * Description:   
 *      Call saHpiUnsubscribe passing in a bad SessionId
 *      Expected return: SA_ERR_HPI_INVALID_SESSION.
 * Line:        P29:47:P29:49
 */

#include <stdio.h>
#include "saf_test.h"

/**********************************************************
*
*   events test -- Call saHpiUnsubscribe passing 
*                               in a bad SessionId
*
*   Expected return:  call returns with an error
*
*   Main Function
*      takes no arguments
*      
*       returns: SAF_TEST_PASS when successfull
*                SAF_TEST_FAIL when an unexpected error occurs
*************************************************************/
int main(int argc, char **argv)
{
	SaHpiSessionIdT session;
	SaErrorT status;
	int retval = SAF_TEST_PASS;

	//
	//  Open the session
	//
	status = saHpiSessionOpen(SAHPI_UNSPECIFIED_DOMAIN_ID, &session, NULL);

	if (status != SA_OK) {
		retval = SAF_TEST_UNRESOLVED;
		e_print(saHpiSessionOpen, SA_OK, status);
	} else {
		//
		//  Call saHpiUnsubscribe passing in a bad SessionId
		//
		status = saHpiUnsubscribe(INVALID_SESSION_ID);
		if (status != SA_ERR_HPI_INVALID_SESSION) {
			e_print(saHpiUnsubscribe,
				SA_ERR_HPI_INVALID_SESSION, status);
			retval = SAF_TEST_FAIL;
		}
		//
		// Close the session
		//
		status = saHpiSessionClose(session);
		if (status != SA_OK) {
			e_print(saHpiSessionClose, SA_OK, status);
		}
	}

	return (retval);
}
